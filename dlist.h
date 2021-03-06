#ifndef _DLIST
#define _DLIST

typedef unsigned int uint;
template<class TYPE>
class Dlist
{
private:
public:
	struct Node
	{
		TYPE data;
		Node* previous = nullptr;
		Node* next = nullptr;

		Node(const TYPE& data) :data(data)
		{}

		~Node()
		{}
	};

	Node* first = nullptr;

	Dlist()
	{}

	~Dlist()
	{}


	bool empty() const
	{
		return first == nullptr;
	}

	uint size() const
	{
		uint n_elements = 0;
		Node* temp = first;
		while (temp != nullptr)
		{
			temp = temp->next;
			n_elements++;
		}
		return n_elements;
	}

	Node* end() const
	{
		Node* temp = first;

		if (temp != nullptr)
		{
			while (temp->next != nullptr)
			{
				temp = temp->next;
			}
		}
		return temp;
	}


	void push_front(const TYPE& data)
	{
		if (first == nullptr)
		{
			first = new Node(data);
		}
		else
		{
			Node* temp = nullptr;
			temp = new Node(data);
			temp->next = first;
			first->previous = temp;
			first = temp;
		}

	}


	void push_back(const TYPE& data)
	{
		Node* temp = first;
		Node* node = new Node(data);
		if (temp == nullptr)
		{
			first = node;
		}
		else
		{
			while (temp->next != nullptr)
			{
				temp = temp->next;
			}
			temp->next = node;
			node->previous = temp;
		}
	}

	bool pop_back()
	{
		if (first != nullptr)
		{
			if (first->next != nullptr)
			{
				Node* copy = first;
				Node* popback = first;
				while (copy->next != nullptr)
				{
					copy = copy->next;
				}
				while (popback->next != copy)
				{
					popback = popback->next;
				}
				popback->next = nullptr;
				delete copy;
				return true;
			}

			else
			{
				Node* popback = first;
				first = nullptr;
				delete popback;
				return true;
			}
		}
		return false;
	}

	bool pop_front()
	{
		if (first != nullptr)
		{
			Node* popfront = first;
			first = popfront->next;
			delete popfront;
			return true;
		}
		return false;
	}

	const Node* first_node() const
	{
		return first;
	}


	bool erase(unsigned int pos)
	{
		if (first != nullptr && pos != 0)
		{
			int i = 0;
			Node* erase = first;
			Node* copy = first;
			while (copy->next != nullptr && i != pos)
			{
				copy = copy->next;
				i++;
			}
			if (i == pos)
			{
				while (erase->next != copy)
				{
					erase = erase->next;
				}
				erase->next = nullptr;
				erase = erase->next;
				delete copy;
				return true;
			}
			delete copy;
			return false;
		}
		if (pos == 0)
		{
			first = first->next;
			delete erase;
		}
		return false;
	}

	void erase(Node* erase)
	{
		if (size() > 1)
		{
			if (erase->previous == nullptr)
			{
				first = erase->next;
				first->previous = nullptr;
			}
			else if (erase->next == nullptr)
			{
				erase->previous->next = nullptr;
			}
			else
			{
				erase->previous->next = erase->next;
				erase->next->previous = erase->previous;
			}
			delete erase;
		}
		else
		{
			first = nullptr;
			delete erase;
		}
	}

	bool insert(const Node* node_insert, int data)
	{
		if (first != nullptr && node_insert != nullptr)
		{
			Node* copy = first;
			Node* insert = new Node(data);
			insert->data = data;
			while (copy->next != node_insert)
			{
				copy = copy->next;
			}

			insert->next = copy->next;
			copy->next = insert;
			return true;
		}
		else
		{
			first = new Node(data);
			first->data = data;
			return true;
		}
		return false;
	}

	void Clear()
	{
		SListNode* n = start;
		SListNode* next;
		while (n != NULL)
		{
			next = n->next;
			delete n;
			n = next;
		}
		start = nullptr;
	}


};


#endif