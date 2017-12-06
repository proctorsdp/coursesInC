#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <algorithm>
#include <iostream> 
#include <assert.h>
#include <sstream>
#include <string>
#include <iomanip>
#include <stdio.h>
#include "Dictionary.hpp"

using namespace std;

// AvlTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x  
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// string toString(string msg )      --> Print tree in sorted order
// Comparable  removeMin  -->  You are not allowed simply to do a find Min and then a remove on that value.  
//                            That would require that you traverse the tree twice  (once to find and once to delete).  We want a true removeMin that 
//                            only traverses in order to delete.
// ******************ERRORS********************************


//HINT:   The class you use as Comparable must have overloaded operators for > == and <.
//        nullptr is another way of saying NULL.  It has some interesting properties for implicit conversions.
//        && is an "rvalue reference".  They are beyond the scope of this class.  A good explanation is at http://thbecker.net/articles/rvalue_references/section_01.html




template <typename Comparable>
class AvlTree
{
public:
	AvlTree() : root{ nullptr }
	{
		size = 0;
	}

	int getSize(){ return size; }
	AvlTree(const AvlTree & rhs) : root{ nullptr }
	{
		size = rhs.size;
		root = clone(rhs.root);
	}

	AvlTree(AvlTree && rhs) : root{ rhs.root }
	{
		rhs.root = nullptr;
	}

	~AvlTree()
	{
		makeEmpty();
	}

	/* Deep copy. */
	AvlTree & operator=(const AvlTree & rhs)
	{
		AvlTree copy = rhs;
		std::swap(*this, copy);
		return *this;
	}

	/* Move. */
	AvlTree & operator=(AvlTree && rhs)
	{
		std::swap(root, rhs.root);

		return *this;
	}
    

	/* Find the smallest item in the tree. Throw UnderflowException if empty. */
	const Comparable & findMin() const
	{
        assert(!isEmpty()) ;
			return findMin(root)->element;
	}

	/* Find the largest item in the tree.	 */
	const Comparable & findMax() const
	{
        assert(!isEmpty()) ;
			return findMax(root)->element;
	}

	/* Returns true if x is found in the tree. */
	bool contains(const Comparable & x) const
	{
		return contains(x, root);
	}

	/* Test if the tree is logically empty.	 */
	bool isEmpty() const
	{
		return root == nullptr;
	}

	/* String contaings the tree contents in sorted order. */
	string toString(string msg) const
	{
		ostringstream oss;
		oss << msg << endl;
		if (isEmpty())
			oss << "Empty tree" << endl;
		else
			oss << toString(root, "");
		oss << endl << "END " << msg << endl;
		return oss.str();
	}
    
    /* String containg the tree contents in list order. */
    string toString2(string msg) const
    {
        ostringstream oss;
        oss << msg << endl;
        if (isEmpty())
            oss << "Empty tree" << endl;
        else
            oss << toString2(root);
        oss << endl << endl << "END " << msg << endl;
        return oss.str();
    }

	/* Make the tree logically empty. */
	void makeEmpty()
	{
		makeEmpty(root);
	}

	/*	Insert x into the tree; 	 */
	void insert(const Comparable & x)
	{
		size++;
        enqueued++;
		insert(x, root);
	}

	/**
	 * Insert x into the tree; 
	 * && is termed an rvalue reference.
	 * a good explanation is at http://thbecker.net/articles/rvalue_references/section_01.html
	 */
	void insert(Comparable && x)
	{
		size++;
        enqueued++;
		insert(std::move(x), root);
	}

	/* Remove x from the tree. Nothing is done if x is not found.	 */
	void remove(const Comparable & x)
	{
		size--;
        dequeued++;
		remove(x, root);
	}
    
	/* remove smallest element from the tree.  Return the value foudn there*/
	Comparable removeMin(){
		size--;
        dequeued++;
		AvlNode * min = removeMin(root);
		assert(min != NULL);
		return min->element;
	}
    
    
    
    /* Solve given Ladder */
    void aStarSolution(string first, string last) {
        solved = false;
        noSolution = false;
        target = true;
        firstWord = first;
        lastWord = last;
        vector<string> word;
        word.push_back(first);
        enqueued = 0;
        dequeued = 0;
        currentLadderSize = 0;
        priorityIncrement = 0;
        
        //fstream fout;
        //fout.open(outputFile);
        //fout.seekp(0, ios::end);
        
        //Title
        cout << "**************************************************************\n" << endl << endl;
        cout << "Find word ladder from \"" << first << "\" to \"" << last << "\"" << endl;
        //Print to file
        //fout << "**************************************************************\n" << endl << endl;
        //fout << "Find word ladder from \"" << first << "\" to \"" << last << "\"" << endl;
        
        
        //Checks if the two words are the same length
        if (first.size() != last.size()) {
            cout << "\"" << first << "\"" << " and " << "\"" << last << "\" are not the same length.\n";
            cout << "Please enter two words of the same length.\n" << endl;
            cout << endl;
            //Print to file
            //fout << "\"" << first << "\"" << " and " << "\"" << last << "\" are not the same length.\n";
            //fout << "Please enter two words of the same length.\n" << endl;
            //fout << endl;
            return;
        }
        
        //Creates a vector of all words from the dictionary that have the same length
        initializeDictionary(int(first.length()));
        
        //Checks if the two words are in the dictionary
        if (!isInDictionary(last) || !isInDictionary(first)) {
            if (target) {
                cout << "\"" << last << "\" was not found in the dictionary.\n";
                //print to file
                //fout << "\"" << last << "\" was not found in the dictionary.\n";
            }
            if(!isInDictionary(first)) {
                cout << "\"" << first << "\" was not found in the dictionary.\n";
                //print to file
                //fout << "\"" << first << "\" was not found in the dictionary.\n";
            }
            cout << endl << endl;
            //print to file
            //fout << endl << endl;
            return;
        }
        //fout.close();
        
        //Creates the first Node
        insert(word);
        
        //If print is true, print the word ladder in each node to the screen
        //if (print) {cout << printList() << endl;}
        
        //Repeats process until ladder is solved
        while(!solved && !noSolution) {
            //outputList();
            
            checkSolution(removeMin());
            //if (print) {cout << printList() << endl;}
        }
        
        //If ladder was solved, output solution
        if (solved) {
            //outputSolution();
            stringstream ss;
            ss << "Ladder Solved using AVL Tree!" << endl;
            ss << "Ladder Size: " << solution.size() << endl;
            ss << "[";
            for (int i = 0; i < solution.size(); i++) {
                ss << solution[i];
                if (i < solution.size() - 1) {
                    ss << ",";
                }
            }
            ss << "]\n";
            ss << "Ladders Enqueued: " << enqueued << endl;
            ss << "Ladders Dequeued: " << dequeued << endl;
            ss << endl << endl;
            cout << ss.str();
            
        }
    }
    
    bool checkSolution(vector<string> currentLadder) {
        if (currentLadder[currentLadder.size() - 1] == lastWord) {
            solution = currentLadder;
            solved = true;
            return true;
        }
        
        isOneAway(currentLadder);
        
        return false;
    }

    //Generates a list of words that are one letter different from the last word on the current ladder
    void isOneAway(vector<string> currentLadder) {
        currentWord = currentLadder[currentLadder.size() - 1];
        string temp;
        int deleteSize = int(oneAway.size());
        
        for (int i = 0; i < deleteSize; i++) {
            oneAway.pop_back();
        }
        
        for (int i = 0; i < currentWord.length(); i++) {
            temp = currentWord;
            for (int j = 0; j < 26; j++) {
                temp[i] = j + 97;
                //cout << temp << endl;     //DEBUG
                if (isInDictionary(temp)) {
                    oneAway.push_back(temp);
                    vector<string> newLadder = currentLadder;
                    newLadder.push_back(oneAway[oneAway.size() - 1]);
                    //cout << toString("TREE") << endl;
                    insert(newLadder);
                    //cout << temp << endl;     //DEBUG
                }
            }
        }
        
        //Only runs if ladder has no solution
        if (oneAway.size() == 0 && root == NULL) {
            cout << "There is no solution for this word ladder.\n" << endl << endl;
            fstream fout;
            fout.open(outputFile);
            fout.seekp(0, ios::end);
            fout << "There is no solution for this word ladder.\n" << endl << endl;
            noSolution = true;
            fout.close();
        }
    }
    
    //Creates a vector of words from the dictionary that are the same length as the user submitted words
    void initializeDictionary(int wordLength) {
        if (dictionary.size() != 0) {
            int dictionaryLength = int(dictionary.size());
            for (int i = 0; i < dictionaryLength; i++) {
                dictionary.pop_back();
                used.pop_back();
                usedAtHeight.pop_back();
            }
            makeEmpty();
        }
        
        string temp;
        fstream fin;
        
        fin.open(fileName);
        while (fin >> temp) {
            if (temp.length() == wordLength) {
                dictionary.push_back(temp);
                used.push_back(false);
                usedAtHeight.push_back(0);
                if (debug) {cout << temp << " - " << temp.length() << endl;}
            }
            else {
                if (debug) {cout << "Discard " << temp << " - " << temp.length() << endl;}
            }
        }
        fin.close();
    }
    
    //Prints a specific number of words contained in the dictionary vector
    void printDictionaryVector(int length) {
        fstream fin;
        string temp;
        
        cout << "First " << length << " entries of the dictionary: \n";
        fin.open(fileName);
        for (int i = 0; i < length; i++) {
            fin >> temp;
            cout << i + 1 << ": " << temp << endl;
        }
        fin.close();
        cout << endl << endl;
    }
    
    //Prints all words contained in the dictionary vector
    void printDictionaryVector() {
        for (int i = 0; i < dictionary.size(); i++) {
            cout << i << ": " << dictionary[i] << endl;
        }
        cout << endl << endl;
    }
    
    //Checks to see if the words is in the dictionary using a binary search
    bool isInDictionary(string word) {
        int first, middle, last;
        first = 0;
        last = int(dictionary.size());
        middle = (first + last) / 2;
        
        while (first <= last) {
            if (debugPrint) {
                cout << word;
                if (word > dictionary[middle]) {
                    cout << " > ";
                }
                else {
                    cout << " < ";
                }
                cout << dictionary[middle] << endl;
                cout << first << " " << middle << " " << last << endl << endl;
            }
            
            if (dictionary[middle] == word) {
                if (target) {
                    target = false;
                    return true;
                }
                if (used[middle] == false || currentLadderSize < usedAtHeight[middle]) {
                    used[middle] = true;
                    return true;
                }
                return false;
            }
            if (word > dictionary[middle]) {
                first = middle + 1;
            }
            else {
                last = middle - 1;
            }
            middle = (first + last) / 2;
        }
        
        return false;
    }

    
    //Sets the name of the dictionary file
    void setFile(string file) {
        fileName = file;
    }
    
    void setOutput(string out) {
        outputFile = out;
    }
    
    int findMinPriority() {
        AvlNode * min = findMin(root);
        if (!min) {return 0;}
        return min->priority;
    }
    

private:
	struct AvlNode
	{
		Comparable element;
		AvlNode   *left;
		AvlNode   *right;
		int       height;
        int priority;

        AvlNode(const Comparable & ele, AvlNode *lt, AvlNode *rt, int h = 0, int p = 0)
            : element{ ele }, left{ lt }, right{ rt }, height{ h }, priority{ p } { }

		AvlNode(Comparable && ele, AvlNode *lt, AvlNode *rt, int h = 0, int p = 0)
            : element{ std::move(ele) }, left{ lt }, right{ rt }, height{ h }, priority { p } { }
	};

	AvlNode *root;
	int size;
    int enqueued;
    int dequeued;
    int currentLadderSize;
    int priorityIncrement;
    
    bool solved;                    //True if ladder is solved
    bool noSolution;                //True if ladder has no solution
    vector<string> dictionary;      //Stores words of a specified length taken from dictionary
    vector<bool> used;              //Tracks whether a word in the dictionary has been used or not
    vector<int> usedAtHeight;
    vector<string> oneAway;         //Stores all words one letter different from a given word
    vector<string> solution;        //Stores the solution to the ladder
    string firstWord, lastWord;     //First word of the ladder & last word of the ladder
    string currentWord;             //The last word of a given ladder
    string fileName;                //Name of dictionary file
    string outputFile;              //Name of txt output file
    bool target;                    //Prevents the last word from being marked 'used' intially
    bool print = false;             //Change to true to print the word ladder contained in each node
    bool debug = false;             //Change to true to debug the dictionary
    bool debugPrint = false;        //Change to true to debug the print function


    int findPriority(Comparable data) {
        int priority = data.size() * data.size();
        bool isWord[lastWord.length()];
        int trueCount = 0;
        for (int i = 0; i < lastWord.length(); i++) {
            isWord[i] = false;
        }
        string currentWord = data[data.size() - 1];
        for (int i = 0; i < lastWord.length(); i++) {
            if (currentWord[i] == lastWord[i]){
                isWord[i] = true;
                priority /= 2;
                trueCount++;
            }
            else {
                priority *= 2;
            }
        }
        if (currentWord == lastWord) {
            priority = -10;
        }
        else if (trueCount == lastWord.length() - 1) {
            priority = (-lastWord.length() * 2);
        }
        return priority;
    }
    
    AvlNode * findMin(AvlNode * subroot) {
        if (!subroot) {return NULL;}
        if (!subroot->left) {
            return subroot;
        }
        AvlNode * min;
        min = findMin(subroot->left);
        return min;
    }
 
    
	/**
	 * Internal method to insert into a subtree.
	 * x is the item to insert.
	 * t is the node that roots the subtree.
	 * Set the new root of the subtree.
	 */
	void insert(const Comparable & x, AvlNode * & t)
	{
        int newPriority = findPriority(x);
		if (t == nullptr)
			t = new AvlNode{ x, nullptr, nullptr, newPriority};
		else if (newPriority < t->priority)
			insert(x, t->left);
		else 
			insert(x, t->right);

		balance(t);
	}

	/**
	 * Internal method to insert into a subtree.
	 * x is the item to insert.
	 * t is the node that roots the subtree.
	 * Set the new root of the subtree.
	 */
	void insert(Comparable && x, AvlNode * & t)
	{
        int newPriority = findPriority(x);
		if (t == nullptr)
            t = new AvlNode{ std::move(x), nullptr, nullptr, newPriority};
		else if (newPriority < t->priority)
			insert(std::move(x), t->left);
		else 
			insert(std::move(x), t->right);

		balance(t);
	}

	/**
	 * Internal method to remove from a subtree.
	 * x is the item to remove.
	 * t is the node that roots the subtree.
	 * Set the new root of the subtree.
	 */
	void remove(const Comparable & x, AvlNode * & t)
	{
		if (t == nullptr)
			return;   // Item not found; do nothing

		if (x < t->element)
			remove(x, t->left);
		else if (t->element < x)
			remove(x, t->right);
		else if (t->left != nullptr && t->right != nullptr) // Two children
		{
			t->element = findMin(t->right)->element;
			remove(t->element, t->right);
		}
		else
		{
			AvlNode *oldNode = t;
			t = (t->left != nullptr) ? t->left : t->right;
			delete oldNode;
		}

		balance(t);
	}

    /*
     * Internal method to remove minimum node from tree.
     * t is the node that roots the subtree.
     * Rebalances tree after deletion.
     */
	AvlNode*  removeMin(AvlNode * & t)
	{
        AvlNode * oldNode;
        if (!t) {return NULL;}
        if (!t->left) {
            //AvlNode * toDelete = t;
            oldNode = t;
            t = t->right;
            //toDelete = NULL;
            //delete toDelete;
            currentLadderSize = (oldNode->element).size();
            return oldNode;
        }
        oldNode = removeMin(t->left);
        balance(t);
        return oldNode;
	}
	static const int ALLOWED_IMBALANCE = 1;

	// Assume t is balanced or within one of being balanced
	void balance(AvlNode * & t)
	{
		if (t == nullptr)
			return;

		if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE)
			if (height(t->left->left) >= height(t->left->right))
				rotateWithLeftChild(t);
			else
				doubleWithLeftChild(t);
		else
			if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE)
				if (height(t->right->right) >= height(t->right->left))
					rotateWithRightChild(t);
				else
					doubleWithRightChild(t);

		t->height = max(height(t->left), height(t->right)) + 1;
	}

	/**
	 * Internal method to find the smallest item in a subtree t.
	 * Return node containing the smallest item.
	 */
	AvlNode * findMin(AvlNode *t) const
	{
		if (t == nullptr)
			return nullptr;
		if (t->left == nullptr)
			return t;
		return findMin(t->left);
	}

	/**
	 * Internal method to find the largest item in a subtree t.
	 * Return node containing the largest item.
	 */
	AvlNode * findMax(AvlNode *t) const
	{
		if (t != nullptr)
			while (t->right != nullptr)
				t = t->right;
		return t;
	}


	/**
	 * Internal method to test if an item is in a subtree.
	 * x is item to search for.
	 * t is the node that roots the tree.
	 */
	bool contains(const Comparable & x, AvlNode *t) const
	{
		if (t == nullptr)
			return false;
		else if (x < t->element)
			return contains(x, t->left);
		else if (t->element < x)
			return contains(x, t->right);
		else
			return true;    // Match
	}

	/**
	 * Internal method to make subtree empty.
	 */
	void makeEmpty(AvlNode * & t)
	{
		if (t != nullptr)
		{
			makeEmpty(t->left);
			makeEmpty(t->right);
			delete t;
		}
		t = nullptr;
	}

	/**
	 * Internal method to crfeate a string for a subtree rooted at t in sorted order.
	 */
	string toString(AvlNode *t, string indent) const
	{
        stringstream ss;
        if (t == NULL) {return ss.str();}
        
        ss << toString(t->right, indent + "        ");
        ss << indent << "[";
        for (int i = 0; i < (t->element).size(); i++) {
            ss << (t->element)[i] << ",";
        }
        ss << "]" << endl;
        ss << toString(t->left, indent + "        ");
        
		return ss.str();
	}
    
    /* 
     * Interal method to create a string for a subtree rooted at t in a list order.
     */
    string toString2(AvlNode *t) const
    {
        stringstream ss;
        if (!t) {return ss.str();}
        
        ss << toString2(t->left);
        ss << "[" << t->element << "]";
        ss << toString2(t->right);
        
        return ss.str();
    }

	/**
	 * Internal method to clone subtree.
	 */
	AvlNode * clone(AvlNode *t) const
	{
		if (t == nullptr)
			return nullptr;
		else
			return new AvlNode{ t->element, clone(t->left), clone(t->right), t->height };
	}
	// Avl manipulations
	/**
	 * Return the height of node t or -1 if nullptr.
	 */
	int height(AvlNode *t) const
	{
		return t == nullptr ? -1 : t->height;
	}

	int max(int lhs, int rhs) const
	{
		return lhs > rhs ? lhs : rhs;
	}

	/**
	 * Rotate binary tree node with left child.
	 * For AVL trees, this is a single rotation for case 1.
	 * Update heights, then set new root.
	 */
	void rotateWithLeftChild(AvlNode * & k2)
	{
		AvlNode *k1 = k2->left;
		k2->left = k1->right;
		k1->right = k2;
		k2->height = max(height(k2->left), height(k2->right)) + 1;
		k1->height = max(height(k1->left), k2->height) + 1;
		k2 = k1;
	}

	/**
	 * Rotate binary tree node with right child.
	 * For AVL trees, this is a single rotation for case 4.
	 * Update heights, then set new root.
	 */
	void rotateWithRightChild(AvlNode * & k1)
	{
		AvlNode *k2 = k1->right;
		k1->right = k2->left;
		k2->left = k1;
		k1->height = max(height(k1->left), height(k1->right)) + 1;
		k2->height = max(height(k2->right), k1->height) + 1;
		k1 = k2;
	}

	/**
	 * Double rotate binary tree node: first left child.
	 * with its right child; then node k3 with new left child.
	 * For AVL trees, this is a double rotation for case 2.
	 * Update heights, then set new root.
	 */
	void doubleWithLeftChild(AvlNode * & k3)
	{
		rotateWithRightChild(k3->left);
		rotateWithLeftChild(k3);
	}

	/**
	 * Double rotate binary tree node: first right child.
	 * with its left child; then node k1 with new right child.
	 * For AVL trees, this is a double rotation for case 3.
	 * Update heights, then set new root.
	 */
	void doubleWithRightChild(AvlNode * & k1)
	{
		rotateWithLeftChild(k1->right);
		rotateWithRightChild(k1);
	}
};

#endif