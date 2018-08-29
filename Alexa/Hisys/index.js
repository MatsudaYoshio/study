'use strict';
const Alexa = require('alexa-sdk');
const constants = require("./constants"); // �萔���Ăяo����悤�ɂ���

var APP_ID = undefined;

// var SKILL_NAME = "�����V�X�e���Y";
// var GET_FACT_MESSAGE = "�m���Ă܂������H";
// var HELP_REPROMPT = "�ǂ����܂����H";

function isAnswerSlotValid(intent) {
    return intent && intent.slots && intent.slots.item && intent.slots.item.resolutions && intent.slots.item.resolutions.resolutionsPerAuthority;
}

exports.handler = function(event, context, callback) {
    var alexa = Alexa.handler(event, context);
    alexa.APP_ID = APP_ID;
    alexa.registerHandlers(handlers);
    alexa.execute();
};

var handlers = {
    'LaunchRequest': function () {
        this.emit(':ask', constants.HISYS_OVERVIEW_MESSAGE + "�����Əڂ����m�肽���ł����H", "�����Əڂ����m�肽���ł����H");
    },
    'HiSysSummaryIntent': function () {
        if(isAnswerSlotValid(this.event.request.intent)){
            if (this.event.request.intent.slots.item.resolutions.resolutionsPerAuthority[0].status.code == 'ER_SUCCESS_MATCH') {
                if(this.event.request.intent.slots.item.resolutions.resolutionsPerAuthority[0].values.length == 1) {
                    this.emit(':tell', constants.DETAIL_MESSAGE[this.event.request.intent.slots.item.resolutions.resolutionsPerAuthority[0].values[0].value.id]);
                }
            }
        }
        
        if(this.event.request.intent.slots.item.value){
            this.emit(':tell', constants.SORRY_MESSAGE + '�A' + this.event.request.intent.slots.item.value + '�ɂ��Ă͔c���ł��Ă��܂���B');
        }else{
            this.emit(':tell', constants.SORRY_MESSAGE + '�A' + '���܂��������܂���B');
        }
    },
    'AMAZON.HelpIntent': function () {
        this.emit(':ask', constants.HELP_MESSAGE, constants.HELP_MESSAGE);
    },
    'AMAZON.CancelIntent': function () {
        this.emit(':tell', constants.STOP_MESSAGE);
    },
    'AMAZON.StopIntent': function () {
        this.emit(':tell', constants.STOP_MESSAGE);
    },
    'SessionEndedRequest': function () {
        // Nothing to do
    }
};
