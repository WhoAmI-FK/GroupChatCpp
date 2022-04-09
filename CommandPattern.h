#pragma once
#include "ObserverPattern.h"

namespace commands {
	class MessageCommand {
	public:
		virtual ~MessageCommand() {};
		virtual void execute() = 0;
		virtual	std::string getMessage() = 0;
	};
	class SendMessageCommand : public MessageCommand{
	private:
		observers::ChatGroup* chatGroup;
		std::string message;
	public:
		SendMessageCommand(observers::ChatGroup* chatGroup, std::string message) :
			chatGroup(chatGroup), message(message) {

		}
		std::string getMessage() override {
			return message;
		}
		void execute() override {
			chatGroup->publish(message);
		}
	};
};
