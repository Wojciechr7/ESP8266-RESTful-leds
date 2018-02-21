var express = require('express');
var router = express.Router();

var Led = require('../models/Led.js');


router.get('/', function(req, res, next) {
  Led.find(function (err, leds) {
    if (err) return next(err);
    res.json(leds);
  });
});



router.put('/:id', function(req, res, next) {
  Led.findByIdAndUpdate(req.params.id, req.body, function (err, post) {
    if (err) return next(err);
    res.json(post);
  });
});


module.exports = router;