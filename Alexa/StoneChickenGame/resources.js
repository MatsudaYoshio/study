'use strict';

const fs = require('fs');
const path = require('path');

const defaultLang = 'ja-JP';
const translations = {};

fs.readdirSync('resources').forEach((file) => {
    const lang = file.replace('.js', '');
    translations[lang] = require(`./${path.join('resources', file)}`);
});

module.exports = translations;