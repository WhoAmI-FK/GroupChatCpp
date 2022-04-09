#pragma once
#include <iostream>
#include <vector>
namespace observers {
	class Subscriber {
	public:
		virtual void notify(const std::string& publisherName, const std::string& message) = 0;
		virtual std::string getName() = 0;
	};
	class Publisher {
	public:
		virtual void subscribe(Subscriber* sub) = 0;
		virtual void unsubscribe(Subscriber* sub) = 0;
		virtual void publish(const std::string& message) = 0;
	};
	class ChatGroup : public Publisher {
	private:
		std::string groupName;
		std::vector<Subscriber*> subs;
	public:
		ChatGroup(const std::string& name) :
			groupName(name) {

		};
		void subscribe(Subscriber* sub) override {
			this->subs.push_back(sub);
		};
		void unsubscribe(Subscriber* sub) override {
			this->subs.erase(std::remove_if(this->subs.begin(), this->subs.end(),
				[sub](Subscriber* s) { return s->getName() == sub->getName(); }), this->subs.end());
		};
		void publish(const std::string& message) override {
			for (auto sub : this->subs) {
				sub->notify(groupName, message);
			}
		};
	};
	class ChatUser : public Subscriber {
	private:
		std::string userName;
	public:
		ChatUser(const std::string& userName) : userName(userName) {

		}
		void notify(const std::string& publisherName,
			const std::string& message) override {
			std::cout << userName << " received a new message from " << publisherName << ": " << message << "\n";
		}
		std::string getName() override {
			return userName;
		}
	};
};