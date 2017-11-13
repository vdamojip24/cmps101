//Vishal Damojipurapu PA1

class List
{

 private class Node{
      // Fields
      int data;//data inside node
      Node next;//use to point to next node
      Node previous;//use to point to previous node
      
      // Constructor
      Node(int data)
      { 
      	this.data = data; 
      	next = null; 
      	previous = null;
      }
      
      // toString():  overrides Object's toString() method
      public String toString()
      { 
         return String.valueOf(data);
      }
      
      // equals(): overrides Object's equals() method
      public boolean equals(Object x){
         boolean eq = false;
         Node that;
         if(x instanceof Node){
            that = (Node) x;
            eq = (this.data==that.data);
         }
         return eq;
      }
   }

//Fields
private Node front;
private Node back;
private Node cursorElement;//content
private int length;
private int cursorIndex;//index of the cursor

// Constructor
// Creates a new empty list.
List()
{
	front = null;
	back = null;
	cursorElement = null;
	length = 0;
	cursorIndex = -1;
}

// Access functions
int length() // Returns the number of elements in this List.
{
	return length;
}

int index() // If cursor is defined, returns the index of the cursor element,
 // otherwise returns -1.
{
	if(cursorElement != null)
	{
		return cursorIndex;
	}
	else
	{
		return -1;
	}
}

int front() // Returns front element of list. Pre: length()>0
{
	if(length >= 1)
	{
		return front.data;
	}
	else
	{
		throw new RuntimeException("Cannot get the front element");
	}
}

int back() // Returns back element of list. Pre: length()>0
{
	if(length() >= 1)
	{
		return back.data;
	}
	else
	{
		throw new RuntimeException("Cannot get the back element");
	}
}

int get() // Returns cursor element. Pre: length()>0, index()>=0
{
	if(length() > 0 && cursorIndex >= 0)
	{
		return cursorElement.data;
	}
	else
	{ 
		throw new RuntimeException("Cannot get the cursor element");
	}
	//return -1;
}

boolean equals(List L) // Returns true if and only if this List and L are the same
 // integer sequence. The states of the cursors in the two Lists
 // are not used in determining equality.
{
	
		Node compareNode1;//create two temp nodes to compare contents 
		Node compareNode2;
		boolean b = false;
		compareNode1 = this.front;
		compareNode2 = L.front;
		if(this.length == L.length)
		{
			b = true;
			while(b && compareNode1 != null)//loops through two nodes to compare
			{
				b = compareNode1.equals(compareNode2);
				compareNode1 = compareNode1.next;
				compareNode2 = compareNode2.next;
			}
		}
	return b;
}

// Manipulation procedures
void clear() // Resets this List to its original empty state.
{
	moveFront();
	cursorElement = null;
	cursorIndex = -1;
	front = back = null;
	length = 0;

}

void moveFront() // If List is non-empty, places the cursor under the front element,
 // otherwise does nothing.
{
	if(length() >= 1)		
	{
		cursorElement = front;
		cursorIndex = 0;
	}
}

void moveBack() // If List is non-empty, places the cursor under the back element,
 // otherwise does nothing.
{
	if(length() >= 1)	
	{
		cursorElement = back;
		cursorIndex = length() - 1;
	}
}

void movePrev() // If cursor is defined and not at front, moves cursor one step toward
 // front of this List, if cursor is defined and at front, cursor becomes
// undefined, if cursor is undefined does nothing.
{
	if(cursorElement != null && cursorElement != front)
	{
		cursorElement = cursorElement.previous;
		cursorIndex--;
	}
	else if(cursorElement != null && cursorElement == front )
	{
		cursorElement = null;
		cursorIndex = -1;
	}
}

void moveNext() // If cursor is defined and not at back, moves cursor one step toward
 // back of this List, if cursor is defined and at back, cursor becomes
 // undefined, if cursor is undefined does nothing.
{
	if(cursorElement != null && cursorElement != back)
	{
		cursorElement = cursorElement.next;
		cursorIndex++;
	}
	else if(cursorElement != null && cursorElement == back)
	{
		cursorElement = null;
		cursorIndex = -1;
	}
}

void prepend(int data) // Insert new element into this List. If List is non-empty,
 // insertion takes place before front element.
{
	Node N = new Node(data);
	if(length() == 0)
	{
		front = back = N;
		length++;
		cursorElement = front = back;
	}
	else
	{	
		front.previous = N;
		N.next = front;
		front = N;
		length++;
		if(cursorElement != null)
		{
			cursorIndex++;
		}
	}
}

void append(int data) // Insert new element into this List. If List is non-empty,
 // insertion takes place after back element.
{
	Node N = new Node(data);
	if(length() == 0)
	{
		front = back = N;
		length++;
	}
	else
	{
		back.next = N;
		N.previous = back;
		back = N;			
		length++;
	}
}

void insertBefore(int data) // Insert new element before cursor.
 // Pre: length()>0, index()>=0
{
	Node N = new Node(data);
	if(length() <= 0 || cursorIndex < 0)
	{
		throw new RuntimeException("Index must be >= 0 or length >0");
	}
	else if(cursorElement == front)
	{
		N.previous = null;;
		N.next = cursorElement;
		cursorElement.previous = N;
		front = N;
		length++;
		cursorIndex++;
	}
	else
	{
		N.next = cursorElement;
		N.previous = cursorElement.previous;
		cursorElement.previous.next = N;
		cursorElement.previous = N;
		length++;
		cursorIndex++;
	}
}

void insertAfter(int data) // Inserts new element after cursor.
 // Pre: length()>0, index()>=0
{
	Node N = new Node(data);
	if(length() <= 0 || index() < 0)
	{
		throw new RuntimeException("Length must be at least 1 or index > 0");
	}
	else if(cursorElement == back)
	{
		N.next = null;
		N.previous = cursorElement;
		cursorElement.next = N;
		back = N;
		length++;
	}
	else
	{
		N.previous = cursorElement;
		N.next = cursorElement.next;
		cursorElement.next.previous = N;
		cursorElement.next = N;
		length++;
	}
}

void deleteFront() // Deletes the front element. Pre: length()>0
{
	if(length() >= 2)
	{
		front = front.next;
		front.previous = null;
		length--;
		cursorIndex--;
	}
	else if (length() == 1) 
	{
		front = back = null;
		length--;
		cursorIndex = -1;
	}
	else
	{
		throw new RuntimeException("Length must be at least 1");
	}
}

void deleteBack() // Deletes the back element. Pre: length()>0
{

	if(length() >= 2)
	{	
		if(cursorElement == back)
		{
			cursorIndex = -1;
		}
		back = back.previous;
		back.next = null;
		length--;
	}
	else if (length() == 1) 
	{
		front = back = null;
		length--;
		cursorIndex = -1;
	}
	else
	{
		throw new RuntimeException("Length must be at least 1");
	}

}

void delete() // Deletes cursor element, making cursor undefined.
 // Pre: length()>0, index()>=0
// Other methods
{
	if(length <= 0 || cursorIndex < 0)
	{
		throw new RuntimeException("cannot delete empty list");
	}
	else if(cursorElement == front)
	{
		deleteFront();
	}
	else if(cursorElement == back)
	{
		deleteBack();
	}
	else
	{
		cursorElement.next.previous = cursorElement.previous;
		cursorElement.previous.next = cursorElement.next;
		cursorElement = null;
		length--;
		cursorIndex = -1;
	}	
}

public String toString() // Overrides Object's toString method. Returns a String
 // representation of this List consisting of a space
// separated sequence of integers, with front on left.
{
	 StringBuffer sb = new StringBuffer();
      Node N = front;
      while(N!=null)
      {
      	sb.append(N.toString());
         if(N.next != null)//makes sure that you only add a space if there is a word after the space
         {
         	sb.append(" ");
         }
         N = N.next;
      }
      return new String(sb);
}

List copy()
	{ // Returns a new List representing the same integer sequence as this
 // List. The cursor in the new list is undefined, regardless of the
 // state of the cursor in this List. This List is unchanged.
		List L = new List();//creates new list that is returned
      	Node N = this.front;

      	while(N != null)
      	{
         	L.append(N.data);
         	N = N.next;
      	}
      	return L;
	}
}	
