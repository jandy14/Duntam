#pragma once
#include "GameFunc.h"

class Node
{
public:
	virtual bool Run() = 0;
};

class CompositeNode : public Node
{
private:
	std::list<Node*> children;
public:
	const std::list<Node*>& GetChildren() const { return children; }
	void AddChild(Node* child) { children.emplace_back(child); }
};

class Selector : public CompositeNode
{
public:
	virtual bool  Run() override
	{
		for (Node* child : GetChildren())
		{
			if (child->Run())
				return true;
		}
		return false;
	}
};

class Sequence : public CompositeNode
{
public:
	virtual bool Run() override
	{
		for (Node* child : GetChildren())
		{
			if (!child->Run())
				return false;
		}
		return true;
	}
};
