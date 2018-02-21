var mongoose = require('mongoose');

var LedSchema = new mongoose.Schema({
    status: Boolean,
    color: String,
    id: Number
});

module.exports = mongoose.model('Led', LedSchema);
