#include "LinkedList.h"
//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

template<class ItemType>
void LinkedList<ItemType>::clear()
{
	while (!isEmpty())
		remove(1);
} // end clear

template<class ItemType>
LinkedList<ItemType>::LinkedList() : headPtr(nullptr), itemCount(0)
{
} // end default constructor

//copy constructor
template<class ItemType>
LinkedList<ItemType>::LinkedList(const LinkedList<ItemType>& aList)
{
} //end copy constructor

template<class ItemType>
LinkedList<ItemType>::~LinkedList()
{
	clear();
} // end destructor

//return whether or not list is empty
template<class ItemType>
bool LinkedList<ItemType>::isEmpty() const
{
	return itemCount > 0;
} //end isEmpty

//return lenght of list
template<class ItemType>
int LinkedList<ItemType>::getLength() const
{
	return itemCount;
} //end getLength

template<class ItemType>
ItemType LinkedList<ItemType>::getEntry(int position) const
throw(PrecondViolatedExcept)
{
	// Enforce precondition
	bool ableToGet = (position >= 1) && (position <= itemCount);
	if (ableToGet)
	{
		Node<ItemType>* nodePtr = getNodeAt(position);
		return nodePtr ->getItem();
	}
	else
	{
		std::string message = "getEntry() called with an empty list or ";
		message = message + "invalid position.";
		throw(PrecondViolatedExcept(message));
	} // end if
} // end getEntry

template<class ItemType>
ItemType LinkedList<ItemType>::replace(int position, const ItemType & newEntry) throw(PrecondViolatedExcept)
{
	return newEntry;
} //end replace

template<class ItemType>
Node<ItemType>* LinkedList<ItemType>::getNodeAt(int position) const
{
	// Debugging check of precondition
	assert((position >= 1) && (position <= itemCount));

	// Count from the beginning of the chain
	Node<ItemType>* curPtr = headPtr;
	for (int skip = 1; skip < position; skip++)
		curPtr = curPtr->getNext();

	return curPtr;
}  // end getNodeAt


template<class ItemType>
bool LinkedList<ItemType>::insert(int newPosition, const ItemType& newEntry)
{
	bool ableToInsert = (newPosition >= 1) && (newPosition <= itemCount + 1);
	if (ableToInsert)
	{
		// Create a new node containing the new entry
		Node<ItemType>* newNodePtr = new Node<ItemType>(newEntry);
		// Attach new node to chain
		if (newPosition == 1)
		{
			// Insert new node at beginning of chain
			newNodePtr ->setNext(headPtr);
			headPtr = newNodePtr;
		}
		else
		{
			// Find node that will be before new node
			Node<ItemType>* prevPtr = getNodeAt(newPosition - 1);

			// Insert new node after node to which prevPtr points
			newNodePtr->setNext(prevPtr->getNext());
			prevPtr->setNext(newNodePtr);
		} // end if

		itemCount++; // Increase count of entries
	}  // end if

	return ableToInsert;
}  // end insert


template<class ItemType>
bool LinkedList<ItemType>::remove(int position)
{
	bool ableToRemove = (position >= 1) && (position <= itemCount);
	if (ableToRemove)
	{
		Node<ItemType>* curPtr = nullptr;
		if (position == 1)
		{
			// Remove the first node in the chain
			curPtr = headPtr; // Save pointer to node
			headPtr = headPtr->getNext();
		}
		else
		{
			// Find node that is before the one to remove
			Node<ItemType>* prevPtr = getNodeAt(position - 1);

			// Point to node to remove
			curPtr = prevPtr->getNext();

			// Disconnect indicated node from chain by connecting the
			// prior node with the one after
			prevPtr->setNext(curPtr->getNext());
		} // end if

		  // Return node to system
		curPtr->setNext(nullptr);
		delete curPtr;
		curPtr = nullptr;
		itemCount--; // Decrease count of entries
	} // end if

	return ableToRemove;
} // end remove

//  // The public method insert:
//template<class ItemType>
//bool LinkedList<ItemType>::insert(int newPosition, const ItemType& newEntry)
//{
//	bool ableToInsert = (newPosition >= 1) && (newPosition <= itemCount + 1);
//	if (ableToInsert)
//	{
//		// Create a new node containing the new entry
//		Node<ItemType>* newNodePtr = new Node<ItemType>(newEntry);
//		headPtr = insertNode(newPosition, newNodePtr, headPtr);
//	} // end if
//	return ableToInsert;
//} // end insert


template<class ItemType>
Node<ItemType>* LinkedList<ItemType>::insertNode(int position, Node<ItemType>* newNodePtr,
	Node<ItemType>* subChainPtr)
{
	if (position == 1)
	{
		// Insert new node at beginning of subchain
		newNodePtr->setNext(subChainPtr);
		subChainPtr = newNodePtr;
		itemCount++;  // Increase count of entries
	}
	else
	{
		Node<ItemType>* afterPtr = insertNode(position - 1, newNodePtr, subChainPtr->getNext());
		subChainPtr->setNext(afterPtr);
	}  // end if

	return subChainPtr;
}  // end insertNode