#include "ObserverPattern.h"
#include "ChainOfResponsibility.h"
using namespace observers;
using namespace validators;
using namespace commands;
int main()
{
	ChatUser* user1 = new ChatUser("Jim");
	ChatUser* user2 = new ChatUser("Barb");
	ChatUser* user3 = new ChatUser("Hannah");
	ChatGroup* group1 = new ChatGroup("Gardening group");
	ChatGroup* group2 = new ChatGroup("Dog-lovers groups");

	group1->subscribe(user1);
	group1->subscribe(user2);
	group2->subscribe(user2);
	group2->subscribe(user3);

	SendMessageCommand* emptyMessage = new SendMessageCommand(group1, "");
	SendMessageCommand* tooShortMessage = new SendMessageCommand(group1, "H");
	SendMessageCommand* sayHelloToGroup1 = new SendMessageCommand(group1, "Hello everyone in group 1!");
	SendMessageCommand* sayHelloToGroup2 = new SendMessageCommand(group2, "Hello everyone in group 2!");
	Handler* sendMessageChain = new BaseHandler;
	sendMessageChain->setNext(new NotEmptyValidator)
		->setNext(new LengthValidator(2))
			->setNext(new PostMessageHandler);
	std::cout << "Sending empty message:\n" <<
		sendMessageChain->handle(emptyMessage) << "\n\n";
	std::cout << "Sending short message: \n" << 
	sendMessageChain->handle(tooShortMessage) << "\n\n";
	std::cout << "Sending message to group 1:\n" <<
		sendMessageChain->handle(sayHelloToGroup1)
		<< "\n\n";
	std::cout << "Sending message to group 2:\n" <<
		sendMessageChain->handle(sayHelloToGroup2)
		<< "\n\n";

	delete user1;
	delete user2;
	delete user3;
	delete group1;
	delete group2;
	delete sendMessageChain;
	delete emptyMessage;
	delete tooShortMessage;
	delete sayHelloToGroup1;
	delete sayHelloToGroup2;
	return 0;
}