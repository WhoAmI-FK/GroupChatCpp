#pragma once
#include "ObserverPattern.h"
#include "CommandPattern.h"
#include <iostream>
#include <string>
#include <regex>
namespace validators {
    class Handler {
    public:
        virtual ~Handler() {};
        virtual Handler* setNext(Handler* nextValidator) = 0;
        virtual std::string handle(commands::MessageCommand* command) = 0;

    };
    class BaseHandler : public Handler {
    protected:
        Handler* next = nullptr;
    public:
        virtual ~BaseHandler() {
            delete next;
        };
        Handler* setNext(Handler* nextValidator) override {
            next = nextValidator;
            return nextValidator;
        };
        virtual std::string handle(commands::MessageCommand* command) override {
            if (this->next) return this->next->handle(command);

            return "Success!";
        }
    };
    class NotEmptyValidator : public BaseHandler {
    public:
        NotEmptyValidator() {};
        std::string handle(commands::MessageCommand* command) override {
            puts("Checking if empty...");
            if (command->getMessage().empty()) return "Please enter a value";
            return BaseHandler::handle(command);
        }
    };
    class LengthValidator : public BaseHandler {
        int _minLength;
    public:
        LengthValidator(int minLength) :
            _minLength(minLength) {

        }
        std::string handle(commands::MessageCommand* command) override {
            puts("Checking string length...");
            if (command->getMessage().length() < _minLength) {
                return "Please enter a value longer than " + std::to_string(_minLength);
            }
            return BaseHandler::handle(command);
        };
    };
    class PostMessageHandler : public BaseHandler {
    public:
        std::string handle(commands::MessageCommand* command) override {
            command->execute();
            return "Message has been Sent!";
        }
   };
};
