#include <iostream>
#include <conio.h>
#include <iomanip>
#include <vector>
#include <stdlib.h>
#include <string>
#include <string.h>

using namespace std;

class LinkedList

{
public:
	struct node
	{
		bool is_friend = false;
		node* next = NULL;
		node()
		{
		}
	};

	node* first = NULL;
	node* last = NULL;

	LinkedList()
	{
		first = NULL;
		last = NULL;
	}

	int size()

	{
		int counter = 0;
		if (last == NULL)
		{
			return 0;
		}
		else if (first == last)
		{
			return 1;
		}
		else
		{
			node* current = first;
			while (current != last)
			{
				current = current->next;
				counter++;
			}
			counter += 1;
			return counter;
		}
	}

	void add()
	{
		node* current = new node();
		current->is_friend = false;
		current->next = NULL;

		if (first != NULL)
		{
			last->next = current;
			last = current;
		}
		else
		{
			first = current;
			last = current;
		}
	}

	void friend_(int index)
	{
		if (size() - 1 < index || index < 0 || first == last)
		{
			cout << endl;
		}

		else
		{
			node* current = first;
			for (int i = 0; i < index; i++)
			{
				current = current->next;
			}
			current->is_friend = true;
		}
	}

	void unfriend_(int index)
	{
		if (size() - 1 < index || index < 0 || first == last)
		{
			cout << endl;
		}

		else
		{
			node* current = first;
			for (int i = 0; i < index; i++)
			{
				current = current->next;
			}
			current->is_friend = false;
		}
	}

	void remove(int index)
	{
		if (size() - 1 < index || index < 0 || first == NULL)
		{
			cout << endl;
		}
		else if (first == last)
		{
			delete first;
			first = NULL;
			last = NULL;
		}
		else if (index == 0)
		{
			node* current = first;
			first = first->next;
			delete current;
		}
		else if (index == size() - 1)
		{
			node* current = first;
			while (current->next != last)
			{
				current = current->next;
			}
			delete last;
			last = current;
			last->next = NULL;
		}
		else
		{
			node* current = first;
			for (int i = 0; i < (index - 1); i++)
			{
				current = current->next;
			}
			node* curr_next = current->next;
			current->next = current->next->next;
			delete curr_next;
		}
	}

	bool isFriend(int index)
	{
		node* curr = first;
		for (int i = 0; i < index; i++)
		{
			curr = curr->next;
		}
		return curr->is_friend;
	}
};

class media
{
public:
	int count = 0;
	struct node2
	{
		int index = -1;
		string name;
		string data;
		node2* next = NULL;
		LinkedList l1;
		node2(string name,string data)
		{
			this->name = name;
			this->data = data;
		}
	};
	node2* head = NULL;
	node2* tail = NULL;

	int size()
	{
		int counter = 0;
		if (head == NULL)
		{
			return 0;
		}
		else if (head == tail)
		{
			return 1;
		}
		else
		{
			node2* current = head;
			while (current != tail)
			{
				current = current->next;
				counter++;
			}
			counter += 1;
			return counter;
		}
	}

	void CreateAccount(string name, string data)
	{
		node2*a = new node2(name,data);
		a->index = count;
		if (count == 0)
		{
			a->l1 = *(new LinkedList());
			a->l1.add();
			head = a;
			tail = a;
			tail->next = NULL;
		}
		else
		{
			tail->next = a;
			tail = a;
			a->l1 = *(new LinkedList());
			node2*curr = head;
			for (int i = 0; i < size(); i++)
			{
				curr->l1.add();

				if (curr != tail)
				{
					a->l1.add();
					curr = curr->next;
				}
			}
		}
		count++;
		cout << "ACCOUNT ADDED"<<endl;
	}


	void deleteAccount(string name)
	{
		if (head != NULL)
		{
			if (head == tail)
			{
				if (head->name == name)
				{
					delete head;
					cout << "ACCOUNT DELETED" << endl;
					head = NULL;
					tail = NULL;
					count = 0;
				}
				else
				{
					cout << "ACCOUNT NOT FOUND" << endl;
				}
			}
			else
			{
				node2* curr = head;
				node2* previous = NULL;
				int foundAt = -5;
				for (int i = 0; i < size(); i++)
				{
					if (name.compare(curr->name) == 0)
					{
						foundAt = curr->index;
						break;
					}


					if (curr != tail)
					{
						previous = curr;
						curr = curr->next;
					}
				}

				if (foundAt == -5)
				{
					cout << "ACCOUNT NOT FOUND" << endl;
					return;
				}
				else if (previous == NULL)
				{
					head = head->next;
					delete curr;
				}
				else if (curr == tail)
				{
					tail = previous;
					tail->next = NULL;
					delete curr;
				}
				else
				{
					previous->next = curr->next;
					delete curr;
				}

				curr = head;
				while (curr != tail)
				{
					if (curr->index > foundAt)
					{
						curr->index = (curr->index - 1);
					}
					curr->l1.remove(foundAt);
					curr = curr->next;
				}
				if (tail->index > foundAt)
				{
					tail->index = (tail->index - 1);
				}
				tail->l1.remove(foundAt);
				count--;
				cout << "ACCOUNT DELETED" << endl;
			}
		}
		else
		{
			cout << "ACCOUNT NOT FOUND" << endl;
		}
	}

	void BecomeFriends(string nameA, string nameB)
	{
		node2* curr = head;
		int friendA = -5;
		int friendB = -5;

		for (int i = 0; i < size(); i++)
		{
			if (curr->name == nameA)
			{
				friendA = curr->index;
			}
			else if (curr->name == nameB)
			{
				friendB = curr->index;
			}

			if (curr != tail)
			{
				curr = curr->next;
			}
		}

		if (friendA != -5 && friendB != -5 && friendA!=friendB)
		{
			node2* currA = head;

			node2* currB = head;

			for (int i = 0; i < size(); i++)
			{
				if (currA->index != friendA)
				{
					currA = currA->next;
				}
				if (currB->index != friendB)
				{
					currB = currB->next;
				}
			}
			currA->l1.friend_(friendB);
			currB->l1.friend_(friendA);
			cout << currA->name << " IS NOW A FRIEND OF " << currB->name<<endl;
		}
		else
		{
			if (friendA == -5)
			{
				cout << nameA << " WAS NOT FOUND" << endl;
			}
			if (friendB == -5)
			{
				cout << nameB << " WAS NOT FOUND"<<endl;
			}
			if (friendA == friendB && friendA != -5)
			{
				cout << nameB << "CAN NOT BE ONES OWN FRIEND" << endl;
			}
		}
	}


	void unFriend(string nameA, string nameB)
	{
		node2* curr = head;
		int friendA = -5;
		int friendB = -5;

		for (int i = 0; i < size(); i++)
		{
			if (curr->name == nameA)
			{
				friendA = curr->index;
			}
			else if (curr->name == nameB)
			{
				friendB = curr->index;
			}

			if (curr != tail)
			{
				curr = curr->next;
			}
		}

		if (friendA != -5 && friendB != -5 && friendA != friendB)
		{
			node2* currA = head;

			node2* currB = head;

			for (int i = 0; i < size(); i++)
			{
				if (currA->index != friendA)
				{
					currA = currA->next;
				}
				if (currB->index != friendB)
				{
					currB = currB->next;
				}
			}
			currA->l1.unfriend_(friendB);
			currB->l1.unfriend_(friendA);
			cout << currA->name << " IS NOW NOT A FRIEND OF " << currB->name<<endl;
		}
		else
		{
			if (friendA == -5)
			{
				cout << nameA << " WAS NOT FOUND" << endl;
			}
			if (friendB == -5)
			{
				cout << nameB << " WAS NOT FOUND" << endl;
			}
			if (friendA == friendB && friendA != -5)
			{
				cout << nameB << "CAN NOT UNFRIEND ONESELF" << endl;
			}
		}
	}

	void displayFriendList(string name)
	{
		if (head == NULL)
		{
			cout << "ACCOUNT NOT FOUND"<<endl;
		}
		else
		{
			bool found = false;
			node2* curr = head;
			for (int i = 0; i < size(); i++)
			{
				if (curr->name == name)
				{
					found = true;
					break;
				}
				else
					curr = curr->next;

			}
			if (found)
			{
				node2* curr2 = head;
				for (int i = 0; i < curr->l1.size(); i++)
				{
					if (curr->l1.isFriend(i))
					{
						cout <<"NAME: "<< curr2->name << endl;
						cout << "BIO: " << curr2->data << endl;
					}

					if (curr2 != tail)
					{
						curr2 = curr2->next;
					}
				}
			}
			else
			{
				cout << "ACCOUNT NOT FOUND"<<endl;
			}
		}
	}

	void searchAccount(string name)
	{
		if (head != NULL)
		{
			bool found = false;
			node2* curr = head;
			for (int i = 0; i < size(); i++)
			{
				if (name.compare(curr->name) == 0)
				{
					found = true;
					cout << "NAME: " << curr->name << endl;
					cout << "BIO: " << curr->data << endl;
					break;
				}

				if (curr != tail)
					curr = curr->next;
			}

			if (!found)
			{
				cout << "ACCOUNT NOT FOUND" << endl;
			}
		}
		else
		{
			cout << "ACCOUNT NOT FOUND"<<endl;
		}
	}

	void suggestFriends(string name)
	{
		if (head != NULL)
		{
			bool found = false;
			node2* curr = head;
			for (int i = 0; i < size(); i++)
			{
				if (name.compare(curr->name) == 0)
				{
					found = true;
					break;
				}

				if (curr != tail)
					curr = curr->next;
			}

			if (!found)
			{
				cout << "ACCOUNT NOT FOUND" << endl;
			}
			else
			{
				//curr is the account
				//curr2 are friends
				//curr3 are friends of friends
				vector<string> names;
				bool added = false;
				node2* curr2 = head;
				for (int i = 0; i < size(); i++)
				{
					if (curr->l1.isFriend(i) && i!=curr->index)
					{
						node2* curr3 = head;
						for (int j = 0; j < curr2->l1.size(); j++)
						{
							if ((!(curr->l1.isFriend(j))) && (curr2->l1.isFriend(j)) && (j!=curr->index))
							{
								added = false;
								for (size_t k = 0; k < (names.size()); k++)
								{
									if (names.at(k) == name)
									{
										added = true;
										break;
									}
								}
								if (!added)
								{
									names.push_back((curr3->name));
								}
							}
							if (curr3 != tail)
							{
								curr3 = curr3->next;
							}
						}
					}
					if (curr2 != tail)
					{
						curr2 = curr2->next;
					}
				}
				if (names.empty())
				{
					curr2 = head;
					for (int i = 0; i < size(); i++)
					{
						if (!curr->l1.isFriend(i) && i != curr->index)
						{
							names.push_back((curr2->name));
						}
						if (curr2 != tail)
						{
							curr2 = curr2->next;
						}
					}
				}
				if (!names.empty())
				{
					for (size_t i = 0; i < names.size(); i++)
					{
						cout << names.at(i) << endl;
					}
				}
				else
				{
					cout << "THIS ACCOUNT IS FRIENDS WITH EVERY AVAILABLE ACCOUNT"<<endl;
				}
			}
		}
		else
		{
			cout << "ACCOUNT NOT FOUND"<<endl;
		}
	}

	void display()
	{
		if (head != NULL)
		{
			node2* curr = head;
			cout << setw(10) << "NAME ";
			for (int i = 0; i < size(); i++)
			{
				cout << setw(10) << curr->name ;
				if (curr != tail)
				{
					curr = curr->next;
				}
			}

			cout << endl;
			curr = head;
			for (int i = 0; i < size(); i++)
			{
				cout << setw(10) << curr->name;
				LinkedList::node* curr2 = curr->l1.first;
				for (int j = 0; j < curr->l1.size(); j++)
				{
					if (curr2->is_friend)
					{
						cout << setw(10) << "1";
					}
					else
					{
						cout << setw(10) << "0";
					}
					if (curr2 != curr->l1.last)
					{
						curr2 = curr2->next;

					}
				}
				cout << endl;
				if (curr != tail)
				{
					curr = curr->next;
				}
			}
		}
		else
		{
			cout << "NO ACCOUNTS FOUND" << endl;
		}
	}

	void mutualFriends(string nameA, string nameB)
	{
		if (head == NULL)
		{
			cout << "ACCOUNTS NOT FOUND" << endl;
		}
		else if (nameA == nameB)
		{
			cout << "CAN NOT FIND MUTUAL FRIENDS OF ONESELF" << endl;
		}
		else
		{
			bool foundA = false;
			bool foundB = false;
			bool foundM = false;

			node2* currA = head;
			node2* currB = head;

			for (int i = 0; i < size(); i++)
			{
				if (currA->name == nameA)
				{
					foundA = true;
				}
				if (currB->name == nameB)
				{
					foundB = true;
				}
				if (currA != tail && !foundA)
				{
					currA = currA->next;
				}
				if (currB != tail && !foundB)
				{
					currB = currB->next;
				}
			}
			if (foundA && foundB && (!currB->l1.isFriend(currA->index)))
			{
				node2* curr2 = head;
				for (int i = 0; i < currA->l1.size(); i++)
				{
					if (currA->l1.isFriend(i) && currB->l1.isFriend(i))
					{
						foundM = true;
						cout << curr2->name << endl;
					}
					if (curr2 != tail)
					{
						curr2 = curr2->next;
					}
				}
				if (!foundM)
				{
					cout << nameA << "THERE ARE NO MUTUAL FRIENDS" << endl;
				}
			}
			else
			{
				if (!foundA)
				{
					cout << nameA << " WAS NOT FOUND" << endl;
				}
				if (!foundB)
				{
					cout << nameB << " WAS NOT FOUND" << endl;
				}
				if (currA->l1.isFriend(currB->index))
				{
					cout << nameA << " IS ALREADY A FRIEND OF "<<nameB << endl;
				}
			}
		}
	}

};

int main()
{
	media m1;
	while (true)
	{
		string option = "-5";
		cout << "WELCOME TO THE SOCIAL NETWORK" << endl << endl;
		cout << "\t1)CREATE ACCOUNT" << endl;
		cout << "\t2)DELETE ACCOUNT" << endl;
		cout << "\t3)SEARCH AN ACCOUNT" << endl;
		cout << "\t4)BECOME FRIENDS" << endl;
		cout << "\t5)COMMON FRIENDS" << endl;
		cout << "\t6)REMOVE FRIEND" << endl;
		cout << "\t7)DISPLAY FRIENDS" << endl;
		cout << "\t8)RECOMMENT FRIENDS" << endl;
		cout << "\t9)DISPLAY GRAPH" << endl;
		cout << "\t0)EXIT" << endl<<endl;
		cout << "ENTER NUMBER BETWEEN 0-9: ";
		cin >> option;

		if (option.compare("1") == 0)
		{
			system("cls");
			cout << "ADD ACCOUNT\n";
			string name;
			string data;
			cout << "NAME: ";
			cin >> name;
			cout << "BIO: ";
			std::getline(std::cin >> std::ws, data);

			m1.CreateAccount(name,data);

			system("pause");
			system("cls");
		}

		else if (option.compare("2") == 0)
		{
			system("cls");
			cout << "DELETE ACCOUNT\n";
			string name;
			cout << "NAME: ";
			cin >> name;
			m1.deleteAccount(name);

			system("pause");
			system("cls");
		}
		else if (option.compare("3") == 0)
		{
			system("cls");
			cout << "SEARCH ACCOUNT\n";
			string name;
			cout << "NAME: ";
			cin >> name;
			m1.searchAccount(name);

			system("pause");
			system("cls");
		}
		else if (option.compare("4") == 0)
		{
			system("cls");
			cout << "MAKE FRIENDS\n";
			string nameA;
			string nameB;
			cout << "NAME OF FIRST PERSON: ";
			cin >> nameA;
			cout << "NAME OF SECOND PERSON: ";
			cin >> nameB;
			m1.BecomeFriends(nameA, nameB);

			system("pause");
			system("cls");
		}

		else if (option.compare("5") == 0)
		{
			system("cls");
			cout << "FIND MUTUAL FRIENDS\n";
			string nameA;
			string nameB;
			cout << "NAME OF FIRST PERSON: ";
			cin >> nameA;
			cout << "NAME OF SECOND PERSON: ";
			cin >> nameB;
			m1.mutualFriends(nameA, nameB);

			system("pause");
			system("cls");
		}

		else if (option.compare("6") == 0)
		{
			system("cls");
			cout << "UNFRIEND AN ACCOUNT\n";
			string nameA;
			string nameB;
			cout << "NAME OF FIRST PERSON: ";
			cin >> nameA;
			cout << "NAME OF SECOND PERSON: ";
			cin >> nameB;
			m1.unFriend(nameA, nameB);

			system("pause");
			system("cls");
		}
		else if (option.compare("7") == 0)
		{
			system("cls");
			cout << "DISPLAY FRIENDLIST\n";
			string name;
			cout << "NAME: ";
			cin >> name;
			m1.displayFriendList(name);

			system("pause");
			system("cls");
		}
		else if (option.compare("8") == 0)
		{
			system("cls");
			cout << "SUGGEST FRIENDS\n";
			string name;
			cout << "NAME: ";
			cin >> name;
			m1.suggestFriends(name);

			system("pause");
			system("cls");
		}
		else if (option.compare("9") == 0)
		{
			cout << "\tDISPLAY\n";
			system("cls");
			m1.display();
			system("pause");
			system("cls");
		}
		else if (option.compare("0") == 0)
		{
			return 0;
		}
		else
		{
			system("cls");
			cout << "\a WRONG INPUT"<<endl;
			system("pause");
			system("cls");
		}
	}
	return 1;

}


