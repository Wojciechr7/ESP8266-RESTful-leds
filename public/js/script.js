var leds;

$(document).ready(function() {

    reloadLeds();

});




function reloadLeds() {
    var data = {};
    $.ajax({
        type: 'GET',
        data: JSON.stringify(data),
        contentType: 'application/json',
        url: 'http://localhost:3000/leds',
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




function updateLed(id, status, dbId) {
    leds[id].status = (status == 'true') ? false : true;
    var data = leds[id];
    $.ajax({
        type: 'PUT',
        data: JSON.stringify(data),
        contentType: 'application/json',
        url: 'http://localhost:3000/leds/' + dbId,
        success: function(data) {
            reloadLeds();
        }
    });


}