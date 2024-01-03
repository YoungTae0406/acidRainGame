#pragma once
#include <string>
#include <cstdlib>
#include <ctime>

const int MAX_STRING_LENGTH = 8;

class MyString {
public:
	int x; int y;
	std::string word;
	int speed;
	bool isCorrect;
	bool isPrint;
	MyString();
	MyString(std::string& w);
};

MyString::MyString() {}
MyString::MyString(std::string& w) : word(w) {
	this->x = 0; this->y = 0;
	this->speed = 0; this->isCorrect = false; this->isPrint = true;
}


class RandomStringComponent {
public:
	virtual std::string getRandomString() = 0;
	virtual ~RandomStringComponent();
};

class BasicString : public RandomStringComponent {
public:
	std::string getRandomString() override;
};

class StringDecorator : public RandomStringComponent {
protected:
	RandomStringComponent* RSC;
public:
	StringDecorator(RandomStringComponent* rsc);
	std::string getRandomString() override;
	virtual ~StringDecorator();
};

class AlphabetDecorator : public StringDecorator {
public:
	AlphabetDecorator(RandomStringComponent* rsc);
	std::string getRandomString() override;
};

class NumberDecorator : public StringDecorator {
public:
	NumberDecorator(RandomStringComponent* rsc);
	std::string getRandomString() override;
};

class SpecialDecorator : public StringDecorator {
public:
	SpecialDecorator(RandomStringComponent* rsc);
	std::string getRandomString() override;
};

RandomStringComponent::~RandomStringComponent() {}

std::string BasicString::getRandomString() {
	std::string result = "";
	
	return result;
}

StringDecorator::StringDecorator(RandomStringComponent* rsc) : RSC(rsc) {}

std::string StringDecorator::getRandomString() {
	return RSC->getRandomString();
}

StringDecorator::~StringDecorator() {
	delete RSC;
}

AlphabetDecorator::AlphabetDecorator(RandomStringComponent* rsc) : StringDecorator(rsc) {}

std::string AlphabetDecorator::getRandomString() {
	std::string charset = "abcdefghijklmnopqrstuvwxyz";
	std::string result = StringDecorator::getRandomString();
	int remainingLength = MAX_STRING_LENGTH - result.length();
	int length = rand() % (remainingLength + 1);
	for (int i = 0; i < length; ++i) {
		result += static_cast<char>('a' + rand() % 26);
	}
	
	return result;
}

NumberDecorator::NumberDecorator(RandomStringComponent* rsc) : StringDecorator(rsc) {}

std::string NumberDecorator::getRandomString() {
	std::string charset = "0123456789";
	std::string result = StringDecorator::getRandomString();
	int remainingLength = MAX_STRING_LENGTH - result.length();
	int length = rand() % (remainingLength + 1);
	for (int i = 0; i < length; ++i) {
		result += std::to_string(rand() % 10);
	}

	return result;
}

SpecialDecorator::SpecialDecorator(RandomStringComponent* rsc) : StringDecorator(rsc) {}

std::string SpecialDecorator::getRandomString() {
	std::string charset = "!@#$%^&*";
	std::string result = StringDecorator::getRandomString();
	int remainingLength = MAX_STRING_LENGTH - result.length();
	int length = rand() % (remainingLength + 1);
	for (int i = 0; i < length; ++i) {
		result += charset[rand() % charset.size()];
	}
	return result;
}