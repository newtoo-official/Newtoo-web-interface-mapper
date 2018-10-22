# WebIDL to C++ converter
Introducing WebIDL2C++ – the first interface draft to real C++ code converter.  
  
WebIDL2C++ is the best solution for your standards-based project.  
Just paste your WebIDL inteface and generate c++ source (.cpp) and header (.h) in two clicks  
Implementing web standarts is faster with this tecnology.  
# Features
- Fully automated
- All basic types, including const
- Supported exception throwings
- Supported regular & readonly attributes
- Supported extended attributes
- Copy constructor for every class
- Customizable namespace
- Automatic inclusion of class headers
- Supported inheritance & partial interfaces
- Supported static & raises exception functions
- Automated private fields
- Supported dictonaties
- Supported enumerations
- Supported pointers
- Crossplatform GUI
- MIT License
## Example
WebIDL interface:
```webidl
[Exposed=Window]
interface Node : EventTarget {
  const unsigned short ELEMENT_NODE = 1;
  const unsigned short ATTRIBUTE_NODE = 2;
  const unsigned short TEXT_NODE = 3;
  
  readonly attribute unsigned short nodeType;
  readonly attribute DOMString nodeName;
  
  [CEReactions] attribute DOMString id;
  [CEReactions] attribute DOMString class;
  
  [SameObject] readonly attribute Node? parentNode;
  
  readonly attribute Node? previousSibling;
  readonly attribute Node? nextSibling;
  
  [CEReactions] Node appendChild(Node node);
  
  boolean hasChildNodes();
  [SameObject] readonly attribute NodeList childNodes;
};

partial interface Node {
  [CEReactions, Unscopable] void remove();
}
```
Generated C++ header:
```c++
#pragma once
#include "EventTarget.h"
#include "DOMString.h"
#include "NodeList.h"
class Node : public EventTarget
{
public:
  Node();
  Node(Node& ref);

  const unsigned short ELEMENT_NODE = 1;
  const unsigned short ATTRIBUTE_NODE = 2;
  const unsigned short TEXT_NODE = 3;
  
  unsigned short nodeType();
  DOMString nodeName();
  
  DOMString id();
  void setId(DOMString aId);
  
  DOMString class();
  void setClass(DOMString aClass);
  
  Node* parentNode() const;
  
  Node* previousSibling();
  Node* nextSibling();
  
  Node* appendChild(Node* node);
  
  bool hasChildNodes();
  NodeList& childNodes();
  
  void remove();
  
protected: /* Auto generated class fields */
  Node* mParentNode;
  NodeList mChildNodes;
};
```
Generated C++ source code:
```c++
#include "Node.h"

Node::Node()
{

}

Node::Node(Node& ref)
 : mParentNode(ref.mParentNode),
   mNodeList(ref.mNodeList)
{}

unsigned short Node::nodeType()
{

}

DOMString Node::nodeName()
{

}

DOMString Node::id()
{

}

void Node::setId(DOMString aId)
{

}

DOMString Node::class()
{

}

void Node::setClass(DOMString aClass)
{

}

Node* Node::parentNode() const
{

}

Node* Node::previousSibling()
{

}

Node* Node::nextSibling()
{

}

Node* Node::appendChild(Node* node)
{

}

bool Node::hasChildNodes()
{

}

NodeList& Node::childNodes()
{

}

void Node::remove()
{

}
```
***
License: [MIT](https://github.com/FlightBlaze/webidl2cpp/blob/master/LICENSE)
