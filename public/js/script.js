var leds;
var socket;

var URL = 'http://192.168.0.101:3000/leds';

$(document).ready(function() {
    socket = io();
    reloadLeds();

    socket.on('update browser', function(){
        reloadLeds();
    });
    socket.on('switch leds', function(){
        switchLeds();
    });

});




function reloadLeds() {
    var data = {};
    $.ajax({
        type: 'GET',
        data: JSON.stringify(data),
        contentType: 'application/json',
        url: URL,
        success: function(data) {
            leds = data;
            $('.led-red').remove();
            $('.led-blue').remove();
            for (var led of data) {
               $('.leds-container').append('<div onclick="updateLed(' + "'" + led.id + "'" + ', ' + "'" + led.status + "'" + ', ' + "'" + led._id + "'" + ')" class="led-' + led.color + '  ' + led.status + '" id="'+led.id+'"></div>');
            }
        }
    });
}

function switchLeds() {
    leds[0].status = !leds[0].status;
    leds[1].status = !leds[1].status;
    socket.emit('event', leds);
    for (var i = 0; i <= 1; i++) {
        $.ajax({
            type: 'PUT',
            data: JSON.stringify(leds[i]),
            contentType: 'application/json',
            url: URL + '/' + leds[i]._id,
            success: function(data) {
                if (--i == 1) {
                    socket.emit('update browser');
                }
            }
        });

    }

}


function updateLed(id, status, dbId) {
    leds[id].status = (status == 'true') ? false : true;
    socket.emit('event', leds);
    var data = leds[id];
    $.ajax({
        type: 'PUT',
        data: JSON.stringify(data),
        contentType: 'application/json',
        url: URL + '/' + dbId,
        success: function(data) {
            socket.emit('update browser');
        }
    });


}