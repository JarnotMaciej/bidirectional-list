/**
 * @file functions.h
 * @author Maciej Jarnot (mj300741@student.polsl.pl)
 * @version 0.1
 * @date 26.01.2023
 *
 */

#pragma once

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <memory>
#include <exception>
#include <iterator>

constexpr auto LOGO = R"(

  ___ _    _ _            _   _               _   _    _    _   
 | _ |_)__| (_)_ _ ___ __| |_(_)___ _ _  __ _| | | |  (_)__| |_ 
 | _ \ / _` | | '_/ -_) _|  _| / _ \ ' \/ _` | | | |__| (_-<  _|
 |___/_\__,_|_|_| \___\__|\__|_\___/_||_\__,_|_| |____|_/__/\__|
                                                                

)";

/** Enum class used for error type marking*/
enum class errorType
{
	notSwappable,
	emptyList,
	nonEmptyList,
	fileNotOpened,
	undefined
};

/**Class used in errors generation*/
class myException
{
	errorType errr; /**< Type of error, errorType enum used for distinction*/

public:
	/** Error constructor, creates error of given error type
	 * @param _errr - errorType to be set
	 */
	myException(errorType _errr) : errr(_errr) {}
	/** Default error constructor, creates error of default error type*/
	myException() : errr(errorType::undefined) {}
	/** Method which translates error types to strings*/
	const char *what()
	{
		switch (errr)
		{
		case errorType::notSwappable:
			return "Node is not swappable! (Next node doesn't exist!)";
		case errorType::emptyList:
			return "List is empty or it has only one element";
		case errorType::nonEmptyList:
			return "List is non empty";
		case errorType::fileNotOpened:
			return "File could not be opened";
		default:
			return "Unknown error.";
		}
	}
};

template <class T>
/**Struct used to store data, node of 'list' class*/
struct listNode
{
	T data;										  /**< Data stored in node*/
	std::shared_ptr<listNode<T>> previousNodePtr; /**< Pointer, which points to the previous element of the list*/
	std::shared_ptr<listNode<T>> nextNodePtr;	  /**< Pointer, which points to the next element of the list*/
	/** Default node constructor, node doesn't hold any data*/
	listNode() = default;
	/** Node constructor, which assigns data and pointers to the previous and the next node
	 * @param other - we take values from 'other' list node and we assign it to another
	 */
	listNode(listNode<T> &other) : data(other.data), previousNodePtr(other.previousNodePtr), nextNodePtr(other.nextNodePtr) {}
};

template <class T>
/**Class used as list*/
class list
{
private:
	std::shared_ptr<listNode<T>> head; /**< Head of the list, points to the first element*/
	std::shared_ptr<listNode<T>> tail; /**< Tail of the list, points to the last element*/
	size_t size = 0;				   /**< Size of the list*/

public:
	/** Default list constructor, creates blank list*/
	list();
	/** Copy constructor, creates a copy of the other list*/
	list(list<T> &otherList);
	/** Move contructor*/
	list(list<T> &&otherList);
	/** Default list destructor*/
	~list();
	/** Method which allows to add element at the end of the list
	 * @param elem - element to add
	 */
	void push_back(T elem);
	/** Method which allows to add element at the beginning of the list
	 * @param elem - element to add
	 */
	void push_front(T elem);
	/** Returns contents of the last element in the list
	 * @return Reference to the last element in the list
	 */
	T &back();
	/** Returns contents of the first element in the list
	 * @return Reference to the first element in the list
	 */
	T &front();
	/** Checks if the container is empty
	 * @return true if the container is empty, false otherwise
	 */
	bool empty();
	/** Deletes node at the end of the list and returns deleted element
	 * @return Deleted element
	 */
	T pop_back();
	/** Deletes node at the beginning of the list and returns deleted element
	 * @return Deleted element
	 */
	T pop_front();
	/**Method which allows to pop element in a chosen position in the list
	 * @param position - position of the element to pop
	 */
	T pop_specified_position(int position);
	/** Method displays all elements of the list*/
	void display();
	/** Search for an element in the list
	 * @param elem - the elements to search for
	 */
	void search(T elem);
	/** Swaps two adjacent elements
	 * @param first - the first element to swap
	 */
	void swap(std::shared_ptr<listNode<T>> first);
	/** Sorts the elements in the list (Bubble sort used)*/
	void sort();
	/** Returns the number of elements in the list
	 * @return The number of elements in the list
	 */
	size_t getSize() { return size; }
	/** Saves the contents of the list to a specified file
	 * @param fileName The name of the file to save the list to
	 */
	void save(std::string fileName);
	/** Opens a list from a specified file
	 * @param fileName The name of the file to open the list from
	 */
	void open(std::string fileName);
	/** Clears the memory by removing all nodes from the list and resets the head and tail pointers*/
	void clear();
	/** Copy assignment operator
	 * @param otherList - the list to copy the contents from
	 * @return A reference to the current list with the copied contents
	 */
	list<T> operator=(list<T> otherList)
	{
		if (&otherList == this)
		{
			return *this;
		}
		else
		{
			if (!empty())
			{

				while (head != nullptr)
				{
					pop_front();
				}
			}

			std::shared_ptr<listNode<T>> pointrr(otherList.head);

			while (pointrr != nullptr)
			{
				push_back(pointrr->data);
				pointrr = pointrr->nextNodePtr;
			}
			return *this;
		}
	}
	/** Move assignment operator
	 * @param otherList - the list to move the contents from
	 * @return A reference to the current list with the moved contents
	 */
	list<T> operator=(list<T> &&otherList) noexcept
	{
		if (this != &otherList)
		{
			clear();
			head = std::move(otherList.head);
			tail = std::move(otherList.tail);
			otherList.clear();
		}

		return *this;
	}

	/** Forward iterator class, used to traverse the list and access the elements stored in it*/
	class iterator
	{
	public:
		/** Constructor for an iterator object
		 * @param p - pointer to the node that the iterator will point
		 */
		iterator(std::shared_ptr<listNode<T>> p) : ptr(p) {}
		/** Dereference operator
		 * @return Returns reference to the element stored in the node
		 */
		T &operator*() { return ptr->data; }
		/** Increment operator - iterator is moved to the next node in the list
		 * @return reference to the next node
		 */
		iterator &operator++()
		{
			ptr = ptr->nextNodePtr;
			return *this;
		}
		/**
		 * Decrement operator - iterator is moved to the previous node in the list
		 * @return reference to the previous node
		 */
		iterator &operator--()
		{
			ptr = ptr->previousNodePtr;
			return *this;
		}
		/** Equality operator
		 * @param other - the other iterator to compare with
		 * @return true if the iterators point to the same node, false otherwise
		 */
		bool operator==(const iterator &other) { return ptr == other.ptr; }
		/** Inequality operator
		 * @param other - the other iterator to compare with
		 * @return true if the iterators point to the different node, false otherwise
		 */
		bool operator!=(const iterator &other) { return ptr != other.ptr; }

	private:
		std::shared_ptr<listNode<T>> ptr; /**< A shared pointer to a listNode, used to traverse the list*/
	};

	/** Returns an iterator pointing to the first element of the list
	 * @return Iterator pointing to the first element of the list
	 */
	iterator begin() { return iterator(head); }
	/** Returns an iterator pointing to the end of the list
	 * @return Iterator pointing to the end of the list
	 */
	iterator end() { return iterator(nullptr); }
};

/*Sample class, used for list class testing*/
class person
{
public:
	/** Default person constructor*/
	person() : name("Jan"), age(32){};
	/** Person constructor, assigns name and age to the person
	 * @param _name The name to assign to the person
	 * @param _age The age to assign to the person
	 */
	person(std::string _name, int _age) : name(_name), age(_age){};
	/** Default person destructor*/
	~person() = default;
	/** Method which allows to change the name
	 * @param _name - new name to assign to the person
	 */
	void setName(std::string _name);
	/** Method to get the name of the person
	 * @return Name of the person
	 */
	std::string getName();
	/** Method to change the age of the person
	 * @param _age - new age to assign to the person
	 */
	void setAge(int _age);
	/** Method to get the age of the person
	 * @return The age of the person
	 */
	int getAge();
	/** Equality operator
	 * @param other - the person to compare to
	 * @return true if the two persons have the same name and age, false otherwise
	 */
	bool operator==(const person &other) const
	{
		return name == other.name && age == other.age;
	}
	/** "Lower than" operator
	 * @param other - the person to compare to
	 * @return true if this person's age is less than the other person's age, false otherwise
	 */
	bool operator<(const person &other);
	/** "Greater than" operator
	 * @param other - the person to compare to
	 * @return true if this person's age is greater than the other person's age, false otherwise
	 */
	bool operator>(const person &other);

	/** Output stream operator
	 * @param s - output stream
	 * @param _person - person to print
	 * @return The output stream
	 */
	friend std::ostream &operator<<(std::ostream &s, const person &_person);

	/** Input stream operator
	 * @param in - The input stream
	 * @param _person - The person to read
	 * @return The input stream
	 */
	friend std::istream &operator>>(std::istream &in, person &_person);

private:
	std::string name; /**< Name of the person*/
	int age;		  /**< Person's age*/
};

/**Function used in debugging, used just to put some space between outputs*/
void gap();

template <class T>
list<T>::list() : head(nullptr), tail(nullptr) {}

template <class T>
list<T>::list(list<T> &otherList)
{
	std::shared_ptr<listNode<T>> pointrr(otherList.head);

	while (pointrr != nullptr)
	{
		push_back(pointrr->data);
		pointrr = pointrr->nextNodePtr;
	}
}

template <class T>
list<T>::list(list<T> &&otherList)
{
	head = std::move(otherList.head);
	tail = std::move(otherList.tail);
	otherList.clear();
}

template <class T>
inline list<T>::~list()
{
	clear();
}

template <class T>
void list<T>::push_back(T elem)
{
	std::shared_ptr<listNode<T>> tmp(new listNode<T>);
	(*tmp).data = elem;
	if (tail == nullptr)
	{
		head = tmp;
		tail = tmp;
		(*tmp).previousNodePtr = nullptr;
		(*tmp).nextNodePtr = nullptr;
	}
	else
	{
		(*tmp).previousNodePtr = tail;
		(*tail).nextNodePtr = tmp;
		tail = tmp;
		tail->nextNodePtr = nullptr;
	}
	size++;
}

template <class T>
void list<T>::push_front(T elem)
{
	std::shared_ptr<listNode<T>> tmp(new listNode<T>);
	(*tmp).data = elem;
	if (tail == nullptr)
	{
		head = tmp;
		tail = tmp;
		(*tmp).previousNodePtr = nullptr;
		(*tmp).nextNodePtr = nullptr;
	}
	else
	{
		(*tmp).nextNodePtr = head;
		(*head).previousNodePtr = tmp;
		head = tmp;
		head->previousNodePtr = nullptr;
	}
	size++;
}

template <class T>
T &list<T>::back()
{
	if (tail == nullptr)
		throw myException();
	return (*tail).data;
}

template <class T>
T &list<T>::front()
{
	if (head == nullptr)
		throw myException();
	return (*head).data;
}

template <class T>
inline bool list<T>::empty()
{
	return !head;
}

template <class T>
inline T list<T>::pop_back()
{
	if (tail == nullptr)
		throw myException();
	std::shared_ptr<listNode<T>> tmp(tail);
	T val = tail->data;
	if (tmp->previousNodePtr != nullptr)
		tmp->previousNodePtr->nextNodePtr = nullptr;
	else
		head = nullptr;
	tail = (tmp->previousNodePtr);
	tmp.reset();
	return val;
}

template <class T>
inline T list<T>::pop_front()
{
	if (head == nullptr)
		throw myException();
	std::shared_ptr<listNode<T>> tmp(head);
	// debug
	T val = (*tmp).data;
	if (tmp->nextNodePtr != nullptr)
		tmp->nextNodePtr->previousNodePtr = nullptr;
	else
		tail = nullptr;
	head = tmp->nextNodePtr;
	tmp.reset();
	return val;
}

template <class T>
inline T list<T>::pop_specified_position(int position)
{
	if (head == nullptr)
		throw myException();
	if (position == 0)
	{
		return pop_front();
	}
	else if (position == size - 1)
	{
		return pop_back();
	}
	else if (position > size - 1 || position < 0)
	{
		throw myException();
	}
	else
	{
		std::shared_ptr<listNode<T>> pointrr(head);
		int elemCounter = 0;
		while (pointrr != nullptr)
		{
			if (position == elemCounter)
			{
				pointrr->previousNodePtr->nextNodePtr = pointrr->nextNodePtr;
				pointrr->nextNodePtr->previousNodePtr = pointrr->previousNodePtr;
				T val = pointrr->data;
				pointrr.reset();
				return val;
			}
			++elemCounter;
			pointrr = pointrr->nextNodePtr;
		}
	}
	throw myException();
}

template <class T>
inline void list<T>::display()
{
	if (head == nullptr)
	{
		std::cout << "\t/Empty list!/" << std::endl;
	}
	else
	{
		std::shared_ptr<listNode<T>> pointrr(head);

		while (pointrr != nullptr)
		{
			std::cout << pointrr->data << std::endl;
			pointrr = pointrr->nextNodePtr;
		}
	}
}

template <class T>
inline void list<T>::search(T elem)
{
	std::shared_ptr<listNode<T>> pointrr(head);
	int elemCounter = 0;
	bool elemFound = false;
	while (pointrr != nullptr)
	{
		if (elem == pointrr->data)
		{
			std::cout << pointrr->data << " at [" << elemCounter << "] position." << std::endl;
			elemFound = true;
		}
		++elemCounter;
		pointrr = pointrr->nextNodePtr;
	}
	if (!elemFound)
		std::cout << elem << " not found." << std::endl;
}

template <class T>
inline void list<T>::swap(std::shared_ptr<listNode<T>> first)
{
	if (first->previousNodePtr == nullptr)
	{
		if (first->nextNodePtr == nullptr)
		{
			throw myException(errorType::notSwappable);
		}
		else
		{
			std::shared_ptr<listNode<T>> second = first->nextNodePtr;
			second->previousNodePtr = nullptr;
			head = second;
			first->previousNodePtr = second;
			first->nextNodePtr = second->nextNodePtr;
			if (second->nextNodePtr != nullptr)
				second->nextNodePtr->previousNodePtr = first;
			second->nextNodePtr = first;
		}
	}
	else
	{
		if (first->nextNodePtr == nullptr)
		{
			throw myException(errorType::notSwappable);
		}
		else
		{
			std::shared_ptr<listNode<T>> second = first->nextNodePtr;
			first->previousNodePtr->nextNodePtr = second;
			second->previousNodePtr = first->previousNodePtr;
			if (second->nextNodePtr != nullptr)
			{
				second->nextNodePtr->previousNodePtr = first;
				first->nextNodePtr = second->nextNodePtr;
			}
			else
			{
				first->nextNodePtr = nullptr;
				tail = first;
			}
			second->nextNodePtr = first;
			first->previousNodePtr = second;
		}
	}
}

template <class T>
inline void list<T>::sort()
{
	if ((head != nullptr) || (head != tail))
	{
		for (int i = 0; i < size - 1; i++)
		{
			auto pointr1 = head;
			auto pointr2 = pointr1->nextNodePtr;
			while (pointr2 != nullptr)
			{
				if ((*pointr2).data < (*pointr1).data)
					swap(pointr1);
				pointr1 = pointr2;
				pointr2 = pointr1->nextNodePtr;
				// std::cout << "pointr1: " <<(*pointr1).data;
				// std::cout << "\npointr2: " <<(*pointr2).data;
			}
		}
	}
}

template <class T>
inline void list<T>::save(std::string fileName)
{
	fileName += ".txt";
	std::ofstream fileToSave(fileName);
	if (fileToSave)
	{
		std::shared_ptr<listNode<T>> pointrr(head);

		while (pointrr != nullptr)
		{
			fileToSave << pointrr->data << std::endl;
			pointrr = pointrr->nextNodePtr;
		}
	}
	else
	{
		throw myException();
	}
}

template <class T>
inline void list<T>::open(std::string fileName)
{
	if (head == nullptr)
	{
		T a;
		std::ifstream openFile(fileName);
		std::string line;
		if (openFile)
		{
			while (std::getline(openFile, line))
			{
				std::istringstream ss(line);
				ss >> a;
				push_back(a);
			}
		}
		else
		{
			throw myException(errorType::fileNotOpened);
		}
	}
	else
	{
		throw myException(errorType::nonEmptyList);
	}
}

template <class T>
inline void list<T>::clear()
{
	while (head != nullptr)
	{
		std::shared_ptr<listNode<T>> temp = head;
		head = head->nextNodePtr;
		temp->previousNodePtr.reset();
		temp->nextNodePtr.reset();
	}

	tail.reset();
	size = 0;
}

/** Function displays a menu of options to the user and allows to interact with it.
 *
 * The menu options include:
 * 0) Open file
 * 1) Save to file
 * 2) Sort list
 * 3) Size
 * 4) Add element - push_back()
 * 5) Add element - push_front()
 * 6) Display list
 * 7) pop_back()
 * 8) pop_front()
 * 9) Quit
 * 10) Display head
 * 11) Display tail
 * 12) Clear the list
 *
 * The user's choice is passed to a switch statement where the corresponding action is executed.
 *
 * @tparam T - type of elements stored in the list
 * @param l - list that the menu will interact with
 */
template <class T>
void menu(list<T> l)
{
	std::cout << LOGO;
	enum class menuChoice
	{
		fileOpen,
		fileWrite,
		sortList,
		size,
		pushBack,
		pushFront,
		display,
		popBack,
		popFront,
		quit,
		head,
		tail,
		clearTheList,
		popAtSpecifiedPos
	};
	std::cout << "------Menu-----\n0) Open file\n1) Save to file\n2) Sort list\n3) Size\n4) Add element - push_back()\n5) Add element - push_front()\n6) Display list\n7) pop_back()\n8) pop_front()\n9) Quit\n10) Display head\n11) Display tail\n12) Clear the list\n13) Pop at specified position";
	gap();
	int choiceNum;
	std::cin >> choiceNum;
	auto choice = static_cast<menuChoice>(choiceNum);
	while (choice != menuChoice::quit)
	{
		switch (choice)
		{
		case menuChoice::fileOpen:
		{

			std::string fileName;
			std::cout << "Enter file name:\n";
			std::cin >> fileName;
			try
			{
				l.open(fileName);
				l.display();
			}
			catch (myException e)
			{
				std::cerr << e.what() << '\n';
			}
		}

		break;
		case menuChoice::fileWrite:
		{
			std::string fileName;
			std::cout << "Enter file name:\n";
			std::cin >> fileName;
			try
			{
				l.save(fileName);
				std::cout << "File saved\n";
			}
			catch (myException e)
			{
				std::cerr << e.what() << '\n';
			}
		}
		break;
		case menuChoice::sortList:
			try
			{
				l.sort();
				std::cout << "List sorted\n";
				l.display();
			}
			catch (myException e)
			{
				std::cerr << e.what() << '\n';
			}
			break;
		case menuChoice::size:
			try
			{
				std::cout << "Size of the list: " << l.getSize() << "\n";
			}
			catch (myException e)
			{
				std::cerr << e.what() << '\n';
			}
			break;
		case menuChoice::pushBack:
			try
			{
				T elemToPush;
				std::cout << "Enter data to push:\n";
				std::cin >> elemToPush;
				std::cout << "\n";
				l.push_back(elemToPush);
				l.display();
			}
			catch (myException e)
			{
				std::cerr << e.what() << '\n';
			}
			break;
		case menuChoice::pushFront:
			try
			{
				T elemToPush;
				std::cout << "Enter data to push:\n";
				std::cin >> elemToPush;
				std::cout << "\n";
				l.push_front(elemToPush);
				l.display();
			}
			catch (myException e)
			{
				std::cerr << e.what() << '\n';
			}
			break;
		case menuChoice::display:
			try
			{
				l.display();
			}
			catch (myException e)
			{
				std::cerr << e.what() << '\n';
			}
			break;
		case menuChoice::popBack:
			try
			{
				T elem = l.pop_back();
				std::cout << "Element deleted: " << elem << "\n";
				l.display();
			}
			catch (myException e)
			{
				std::cerr << e.what() << '\n';
			}
			break;
		case menuChoice::popFront:
			try
			{
				T elem = l.pop_front();
				std::cout << "Element deleted: " << elem << "\n";
				l.display();
			}
			catch (myException e)
			{
				std::cerr << e.what() << '\n';
			}
			break;
		case menuChoice::head:
			try
			{
				std::cout << "Head: " << l.front() << "\n";
			}
			catch (myException e)
			{
				std::cerr << e.what() << '\n';
			}
			break;
		case menuChoice::tail:
			try
			{
				std::cout << "Tail: " << l.back() << "\n";
			}
			catch (myException e)
			{
				std::cerr << e.what() << '\n';
			}
			break;
		case menuChoice::clearTheList:
			try
			{
				l.clear();
				l.display();
			}
			catch (myException e)
			{
				std::cerr << e.what() << '\n';
			}
			break;
		case menuChoice::popAtSpecifiedPos:
			try
			{
				int pos;
				std::cout << "Enter position to delete: \n";
				std::cin >> pos;
				std::cout << "Element deleted: " << l.pop_specified_position(pos) << "\n";
				l.display();
			}
			catch (myException e)
			{
				std::cerr << e.what() << '\n';
			}
			break;
		default:
			break;
		}
		gap();
		std::cin >> choiceNum;
		choice = static_cast<menuChoice>(choiceNum);
	}
}

#endif /* FUNCTIONS_H */