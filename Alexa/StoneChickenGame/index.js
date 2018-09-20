"use strict";
const Alexa = require("alexa-sdk");

const STATES = {
    START: "START",
    STOP: "STOP",
    EXPLANATION: "EXPLANATION",
    DECIDE_FIRST: "DECIDE_FIRST",
    COIN_GAME: "COIN_GAME",
    GAMEOVER: "GAMEOVER"
};

const MAX_COIN_NUMBER = 30;
const MIN_GET_NUMBER = 1;
const MAX_GET_NUMBER = 5;

function calculate_next_number(coin_num) {
    if (Math.random() < 0.2) {
        return Math.floor(Math.random() * MAX_GET_NUMBER) + MIN_GET_NUMBER;
    } else {
        const r = coin_num % MAX_GET_NUMBER;
        if (r > 2) {
            return r - 2;
        } else if (r < 2) {
            return MAX_GET_NUMBER + r - 2;
        } else {
            return Math.floor(Math.random() * MAX_GET_NUMBER) + MIN_GET_NUMBER;
        }
    }
}

function get_user_number(intent) {
    if (intent.slots.number && intent.slots.number.value) {
        let num_str = intent.slots.number.value;
        if (num_str.match(/枚/)) {
            num_str = num_str.slice(0, -1);
        }

        let number = Number(num_str);
        if (!isNaN(number)) {
            return number;
        }
    }

    return undefined;
}

exports.handler = function (event, context, callback) {
    const alexa = Alexa.handler(event, context, callback);
    alexa.appId = process.env.APP_ID;
    alexa.resources = require("./resources.js");
    alexa.registerHandlers(
        newSessionHandlers,
        startStateHandlers,
        stopStateHandlers,
        explanationStateHandlers,
        decideFirstStateHandlers,
        coinGameStateHandlers,
        gameOverStateHandlers
    );
    alexa.execute();
};

const newSessionHandlers = {
    "LaunchRequest": function () {
        this.attributes["previous_state"] = STATES.START;

        this.handler.state = STATES.START;
        this.emitWithState("NewGame");
    },
    "AMAZON.StartOverIntent": function () {
        this.handler.state = STATES.START;
        this.emitWithState("NewGame");
    },
    "AMAZON.HelpIntent": function () {
        this.handler.state = STATES.START;
        this.emitWithState("AMAZON.HelpIntent");
    },
    "AMAZON.CancelIntent": function () {
        this.attributes["previous_state"] = this.handler.state;
        this.handler.state = STATES.STOP;
        this.emitWithState("Stop");
    },
    "AMAZON.StopIntent": function () {
        this.attributes["previous_state"] = this.handler.state;
        this.handler.state = STATES.STOP;
        this.emitWithState("Stop");
    },
    "Unhandled": function () {
        this.emit(":ask", this.t("UNHANDLED_MESSAGE"));
    },
    "SessionEndedRequest": function () { }
};

const startStateHandlers = Alexa.CreateStateHandler(STATES.START, {
    "NewGame": function () {
        this.attributes["current_coin_number"] = MAX_COIN_NUMBER;

        this.emit(":ask", this.t("START_MESSAGE"), this.t("START_MESSAGE"));
    },
    "AMAZON.YesIntent": function () {
        this.handler.state = STATES.EXPLANATION;
        this.emitWithState("Explanation");
    },
    "AMAZON.NoIntent": function () {
        this.handler.state = STATES.DECIDE_FIRST;
        this.emitWithState("DecideFirst");
    },
    "AMAZON.RepeatIntent": function () {
        this.emit(":ask", this.t("START_MESSAGE"), this.t("START_MESSAGE"));
    },
    "AMAZON.HelpIntent": function () {
        this.emit(":ask", this.t("HELP_MESSAGE")[this.handler.state], this.t("HELP_MESSAGE")[this.handler.state]);
    },
    "AMAZON.CancelIntent": function () {
        this.attributes["previous_state"] = this.handler.state;
        this.handler.state = STATES.STOP;
        this.emitWithState("Stop");
    },
    "AMAZON.StopIntent": function () {
        this.attributes["previous_state"] = this.handler.state;
        this.handler.state = STATES.STOP;
        this.emitWithState("Stop");
    },
    "Unhandled": function () {
        this.emit(":ask", this.t("UNHANDLED_MESSAGE"), this.t("START_MESSAGE"));
    },
    "SessionEndedRequest": function () { }
});

const stopStateHandlers = Alexa.CreateStateHandler(STATES.STOP, {
    "Stop": function () {
        this.emit(":ask", this.t("STOP_MESSAGE"), this.t("STOP_MESSAGE"));
    },
    "AMAZON.YesIntent": function () {
        this.emit(":tell", this.t("END_MESSAGE"));
    },
    "AMAZON.NoIntent": function () {
        this.handler.state = this.attributes["previous_state"];
        this.emitWithState("AMAZON.HelpIntent");
    },
    "AMAZON.RepeatIntent": function () {
        this.emit(":ask", this.t("STOP_MESSAGE"), this.t("STOP_MESSAGE"));
    },
    "AMAZON.HelpIntent": function () {
        this.emit(":ask", this.t("HELP_MESSAGE")[this.handler.state], this.t("HELP_MESSAGE")[this.handler.state]);
    },
    "AMAZON.CancelIntent": function () {
        this.emit(":tell", this.t("END_MESSAGE"));
    },
    "AMAZON.StopIntent": function () {
        this.emit(":tell", this.t("END_MESSAGE"));
    },
    "Unhandled": function () {
        this.emit(":ask", this.t("UNHANDLED_MESSAGE"), this.t("STOP_MESSAGE"));
    },
    "SessionEndedRequest": function () { }
});

const explanationStateHandlers = Alexa.CreateStateHandler(STATES.EXPLANATION, {
    "Explanation": function () {
        this.emit(":ask", this.t("EXPLANATION_MESSAGE"), this.t("EXPLANATION_MESSAGE"));
    },
    "AMAZON.YesIntent": function () {
        this.handler.state = STATES.DECIDE_FIRST;
        this.emitWithState("DecideFirst");
    },
    "AMAZON.NoIntent": function () {
        this.handler.state = STATES.START;
        this.emitWithState("AMAZON.HelpIntent");
    },
    "AMAZON.RepeatIntent": function () {
        this.emit(":ask", this.t("EXPLANATION_MESSAGE"), this.t("EXPLANATION_MESSAGE"));
    },
    "AMAZON.HelpIntent": function () {
        this.emit(":ask", this.t("HELP_MESSAGE")[this.handler.state], this.t("HELP_MESSAGE")[this.handler.state]);
    },
    "AMAZON.CancelIntent": function () {
        this.attributes["previous_state"] = this.handler.state;
        this.handler.state = STATES.STOP;
        this.emitWithState("Stop");
    },
    "AMAZON.StopIntent": function () {
        this.attributes["previous_state"] = this.handler.state;
        this.handler.state = STATES.STOP;
        this.emitWithState("Stop");
    },
    "Unhandled": function () {
        this.emit(":ask", this.t("UNHANDLED_MESSAGE"), this.t("EXPLANATION_MESSAGE"));
    },
    "SessionEndedRequest": function () { }
});

const decideFirstStateHandlers = Alexa.CreateStateHandler(STATES.DECIDE_FIRST, {
    "DecideFirst": function () {
        this.emit(":ask", this.t("DECIDE_FIRST_MESSAGE"), this.t("DECIDE_FIRST_MESSAGE"));
    },
    "DecideFirstIntent": function () {
        if (this.event.request.intent && this.event.request.intent.slots && this.event.request.intent.slots.order && this.event.request.intent.slots.order.resolutions && this.event.request.intent.slots.order.resolutions.resolutionsPerAuthority) {
            if (this.event.request.intent.slots.order.resolutions.resolutionsPerAuthority[0].status.code == 'ER_SUCCESS_MATCH') {
                if (this.event.request.intent.slots.order.resolutions.resolutionsPerAuthority[0].values.length == 1) {
                    switch (this.event.request.intent.slots.order.resolutions.resolutionsPerAuthority[0].values[0].value.id) {
                        case "FIRST":
                            this.handler.state = STATES.COIN_GAME;
                            this.emitWithState("UserStart");
                            break;
                        case "SECOND":
                            this.handler.state = STATES.COIN_GAME;
                            this.emitWithState("AlexaStart");
                            break;
                        case "ANY":
                            this.handler.state = STATES.COIN_GAME;
                            if (Math.random() < 0.5) {
                                this.emitWithState("UserStart", true);
                            } else {
                                this.emitWithState("AlexaStart", true);
                            }
                            break;
                    }
                }
            }
        }

        if (this.event.request.intent.slots.order.value) {
            this.emit(":ask", this.t("CANT_DECIDE_ORDER_MESSAGE"), this.t("DECIDE_FIRST_MESSAGE"));
        } else {
            this.emit(":ask", this.t("UNHANDLED_MESSAGE"), this.t("DECIDE_FIRST_MESSAGE"));
        }
    },
    "AMAZON.RepeatIntent": function () {
        this.emit(":ask", this.t("DECIDE_FIRST_MESSAGE"), this.t("DECIDE_FIRST_MESSAGE"));
    },
    "AMAZON.HelpIntent": function () {
        this.emit(":ask", this.t("HELP_MESSAGE")[this.handler.state], this.t("HELP_MESSAGE")[this.handler.state]);
    },
    "AMAZON.CancelIntent": function () {
        this.attributes["previous_state"] = this.handler.state;
        this.handler.state = STATES.STOP;
        this.emitWithState("Stop");
    },
    "AMAZON.StopIntent": function () {
        this.attributes["previous_state"] = this.handler.state;
        this.handler.state = STATES.STOP;
        this.emitWithState("Stop");
    },
    "Unhandled": function () {
        this.emit(":ask", this.t("UNHANDLED_MESSAGE"), this.t("DECIDE_FIRST_MESSAGE"));
    },
    "SessionEndedRequest": function () { }
});

const coinGameStateHandlers = Alexa.CreateStateHandler(STATES.COIN_GAME, {
    "AlexaStart": function (randomized = false) {
        const next_num = calculate_next_number();
        this.attributes["current_coin_number"] -= next_num;

        let output_message = this.t("ALEXA_START_MESSAGE") + "私はコインを" + String(next_num) + "枚取ります。これでコインは残り" + String(this.attributes["current_coin_number"]) + "枚です。<break time=\"500ms\"/>次はあなたの番です。コインを何枚取りますか？";

        if (randomized) {
            output_message = "では、私が適当に決めます。<break time=\"1500ms\"/>決まりました。私が先攻で行きます。<break time=\"1s\"/>" + output_message;
        }

        this.emit(":ask", output_message, output_message);
    },
    "UserStart": function (randomized = false) {
        let output_message = "それではゲームを始めます。あなたからコインを取ってください。コインは残り" + String(this.attributes["current_coin_number"]) + "枚です。<break time=\"500ms\"/>コインを何枚取りますか？";

        if (randomized) {
            output_message = "では、私が適当に決めます。<break time=\"1500ms\"/>決まりました。私が後攻で行きます。" + output_message;
        }

        this.emit(":ask", output_message, output_message);
    },
    "GetNumberIntent": function () {
        if (this.event.request.intent && this.event.request.intent.slots && this.event.request.intent.slots.number) {
            const get_num = get_user_number(this.event.request.intent);

            if (typeof get_num === "undefined") {
                this.emit(":ask", this.t("UNKNOWN_COIN_MESSAGE") + this.t("ONE_MORE_COIN_MESSAGE"), this.t("ONE_MORE_COIN_MESSAGE"));
            }

            if (get_num >= this.attributes["current_coin_number"]) {
                this.emit(":ask", "コインの残り枚数を考えると、そのような枚数のコインは取れません。<break time=\"500ms\"/>" + this.t("ONE_MORE_COIN_MESSAGE") + "<break time=\"500ms\"/>ちなみに、コインは残り" + String(this.attributes["current_coin_number"]) + "枚です。", "もう一度取りたいコインの枚数を教えてください。");
            } else if (get_num < MIN_GET_NUMBER || get_num > MAX_GET_NUMBER) {
                this.emit(":ask", "そのような枚数のコインは取れません。一度に取れるコインの数はいち以上五以下です。<break time=\"500ms\"/>" + this.t("ONE_MORE_COIN_MESSAGE") + "<break time=\"500ms\"/>ちなみに、コインは残り" + String(this.attributes["current_coin_number"]) + "枚です。", this.t("ONE_MORE_COIN_MESSAGE"));
            } else {
                this.attributes["current_coin_number"] -= get_num;
                const previous_coin_number = this.attributes["current_coin_number"];

                if (this.attributes["current_coin_number"] == 1) {
                    this.handler.state = STATES.GAMEOVER;
                    this.emitWithState("GameOver", this.t("AHA_MESSAGE")[Math.floor(Math.random() * this.t("AHA_MESSAGE").length)] + "これでコインは残り一枚なので、私の負けです。");
                }

                if (this.attributes["current_coin_number"] <= MAX_GET_NUMBER + 1) {
                    this.handler.state = STATES.GAMEOVER;
                    this.emitWithState("GameOver", this.t("AHA_MESSAGE")[Math.floor(Math.random() * this.t("AHA_MESSAGE").length)] + "これでコインは残り" + String(previous_coin_number) + "枚です。<break time=\"500ms\"/>次は私の番ですね。私はコインを" + String(this.attributes["current_coin_number"] - 1) + "枚取ります。<break time=\"500ms\"/>これでコインは残り1枚で、次はあなたの番です。つまり、私の勝ちです。");
                } else {
                    const next_num = calculate_next_number();
                    this.attributes["current_coin_number"] -= next_num;

                    const output_message = this.t("AHA_MESSAGE")[Math.floor(Math.random() * this.t("AHA_MESSAGE").length)] + "これでコインは残り" + String(previous_coin_number) + "枚です。<break time=\"500ms\"/>次は私の番ですね。私はコインを" + String(next_num) + "枚取ります。これでコインは残り" + String(this.attributes["current_coin_number"]) + "枚です。<break time=\"500ms\"/>次はあなたの番です。コインを何枚取りますか？";
                    this.emit(":ask", output_message, output_message);
                }
            }
        }

        if (this.event.request.intent.slots.number.value) {
            this.emit(":ask", this.t("UNKNOWN_COIN_MESSAGE") + this.t("ONE_MORE_COIN_MESSAGE"), this.t("ONE_MORE_COIN_MESSAGE"));
        } else {
            this.emit(":ask", this.t("UNHANDLED_MESSAGE"), this.t("ONE_MORE_COIN_MESSAGE"));
        }
    },
    "CheckCoinIntent": function () {
        const output_message = "コインは残り" + String(this.attributes["current_coin_number"]) + "枚です。<break time=\"500ms\"/>次はあなたの番です。コインを何枚取りますか？";
        this.emit(":ask", output_message, output_message);
    },
    "AMAZON.HelpIntent": function () {
        const output_message = this.t("HELP_MESSAGE")[this.handler.state] + "<break time=\"500ms\"/>ちなみに、コインは残り" + String(this.attributes["current_coin_number"]) + "枚です。";
        this.emit(":ask", output_message, output_message);
    },
    "AMAZON.CancelIntent": function () {
        this.attributes["previous_state"] = this.handler.state;
        this.handler.state = STATES.STOP;
        this.emitWithState("Stop");
    },
    "AMAZON.StopIntent": function () {
        this.attributes["previous_state"] = this.handler.state;
        this.handler.state = STATES.STOP;
        this.emitWithState("Stop");
    },
    "Unhandled": function () {
        this.emit(":ask", this.t("UNHANDLED_MESSAGE"), this.t("ONE_MORE_COIN_MESSAGE"));
    },
    "SessionEndedRequest": function () { }
});

const gameOverStateHandlers = Alexa.CreateStateHandler(STATES.GAMEOVER, {
    "GameOver": function (game_over_message) {
        game_over_message += "<break time=\"500ms\"/>" + this.t("ONE_MORE_GAME_MESSAGE");
        this.emit(":ask", game_over_message, this.t("ONE_MORE_GAME_MESSAGE"));
    },
    "AMAZON.YesIntent": function () {
        this.handler.state = STATES.START;
        this.emitWithState("NewGame");
    },
    "AMAZON.NoIntent": function () {
        this.emit(":tell", this.t("END_MESSAGE"));
    },
    "AMAZON.RepeatIntent": function () {
        this.emit(":ask", this.t("ONE_MORE_GAME_MESSAGE"), this.t("ONE_MORE_GAME_MESSAGE"));
    },
    "AMAZON.HelpIntent": function () {
        this.emit(":ask", this.t("HELP_MESSAGE")[this.handler.state], this.t("HELP_MESSAGE")[this.handler.state]);
    },
    "AMAZON.CancelIntent": function () {
        this.emit(":tell", this.t("END_MESSAGE"));
    },
    "AMAZON.StopIntent": function () {
        this.emit(":tell", this.t("END_MESSAGE"));
    },
    "Unhandled": function () {
        this.emit(":ask", this.t("UNHANDLED_MESSAGE"), this.t("ONE_MORE_GAME_MESSAGE"));
    },
    "SessionEndedRequest": function () { }
});