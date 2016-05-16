#include <iostream>
using namespace std;

#define ALPHABETS 33

class Node {
public:
    Node(char letter){ 
		value = 0;
		mContent = letter; 
		end = false; 
		parent = NULL;
		for (int index = 0; index < ALPHABETS; index++)
		{
			mChildren[index] = NULL;        
		}
	}
    ~Node() {
		//cout << "deleting " << mContent << endl;
	}
	int get_value(){ 
		return value; 
	}
    void set_value(int i) { 
		value = i; 
	}
    char get_letter(){ 
		return mContent; 
	}
    void set_letter(char c) { 
		mContent = c; 
	}
    bool get_end() { 
		return end; 
	}
    void set_end(bool b) { 
		end = b; 
	}
	Node* get_child(char c){

		int index = tolower(c) - 'a';

		if(index < 0 || index >= ALPHABETS){
			return NULL;
		}

		return mChildren[index];
	}
	Node* add_child(char c){

		int index = tolower(c) - 'a';

		if(index < 0 || index >= ALPHABETS){
			return NULL;
		}

		if(mChildren[index] == NULL){
			mChildren[index] = new Node(c);
			mChildren[index]->parent  = this;
		}

		return mChildren[index];
	}

	bool delete_child(char c){

		int index = tolower(c) - 'a';

		if(index < 0 || index >= ALPHABETS){
			return false;
		}

		if(mChildren[index] != NULL){
			delete mChildren[index];
			mChildren[index] = NULL;
		}

		return true;
	}

	Node* get_parent(){
		return parent;
	}

	void get_values_longer_than(int longer_than, int curr_step){
		if(end && (curr_step > longer_than)){
			cout << value << endl;
		}

		for (int index = 0; index < ALPHABETS; index++)
		{
			if(mChildren[index] != NULL){
				mChildren[index]->get_values_longer_than(longer_than, curr_step + 1);
			}
		}
	}

	void get_depth(int curr_max, int& max){
		if(curr_max > max){
			max = curr_max;
		}

		for (int index = 0; index < ALPHABETS; index++)
		{
			if(mChildren[index] != NULL){

				mChildren[index]->get_depth(curr_max + 1, max);
			}
		}
	}

	void delete_nodes_with_current_depth(int depth, int curr_depth){
		if(curr_depth == depth){
			for (int index = 0; index < ALPHABETS; index++)
			{
				if(mChildren[index] != NULL){
					delete mChildren[index];
					mChildren[index] = NULL;
				}
			}
		}

		for (int index = 0; index < ALPHABETS; index++)
		{
			if(mChildren[index] != NULL){
				mChildren[index]->delete_nodes_with_current_depth(depth, curr_depth + 1);
			}
		}
	}

private:
    char mContent;
    bool end;
	int value;
    Node* mChildren[ALPHABETS];
	Node* parent;
};

class Trie {
public:
    Trie(){
		root = new Node(' ');
	}
    ~Trie(){
		int max_depth = 0;
		root->get_depth(0, max_depth);

		for(int i = max_depth; i >= 0; i--){
			root->delete_nodes_with_current_depth(i, 0);
		}
	}
    void add_word(string, int);
    bool search_word(string, int&);
    bool delete_word(string);
	void print_values_longer_than(string);

private:
    Node* root;
};

void Trie::add_word(string s, int value)
{
    Node* current_node = root;

    if ( s.length() == 0 )
    {
        return;
    }

    for ( int i = 0; i < s.length(); i++ )
    {        
        Node* child_node = current_node->get_child(s[i]);

		if(child_node == NULL){
			child_node = current_node->add_child(s[i]);
		}

        current_node = child_node;
    }

	if(current_node == NULL){
		return;
	}
	current_node->set_end(true);
	current_node->set_value(value);
}


bool Trie::search_word(string s, int& value)
{
    Node* current_node = root;
	Node* child_node;

    if ( s.length() == 0 )
    {
        return false;
    }

    for ( int i = 0; i < s.length(); i++ )
    {        
        child_node = current_node->get_child(s[i]);

		if(child_node == NULL){
			return false;
		}

        current_node = child_node;
    }

	value = current_node->get_value();
	return current_node->get_end();

	return false;
}

bool Trie::delete_word(string s)
{
    Node* current_node = root;
	Node* child_node;
	Node* parent_node;

    if ( s.length() == 0 )
    {
        return false;
    }

    for ( int i = 0; i < s.length(); i++ )
    {        
        child_node = current_node->get_child(s[i]);

		if(child_node == NULL){
			return false;
		}

        current_node = child_node;
    }

	current_node->set_end(false);

	for ( int i = s.length() - 1; i >= 0; i-- )
    {        
		if(current_node->get_end()){

			return true;
		}

        parent_node = current_node->get_parent();

		parent_node->delete_child(s[i]);

        current_node = parent_node;
    }

	return true;
}

void Trie::print_values_longer_than(string word){
	root->get_values_longer_than(word.length(), 0);
}

int main()
{
	int return_value = 0;
    Trie* trie = new Trie();
    trie->add_word("alpha", 1);
    trie->add_word("beta", 2);
    trie->add_word("gamma", 3);
	trie->add_word("dellta", 4);
	trie->add_word("epsilon", 5);

	trie->delete_word("dellta");

	trie->print_values_longer_than("gamma");

    delete trie;
}
