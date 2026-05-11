#pragma once 

class Identi{
	int ID;
public:
    Identi(int id = 0) : ID(id) {}
    int getID() const { return ID; }
    bool operator==(const Identi& other) const {
        return ID == other.ID;
    }
};

class ParamId {
    int objectID_;
    int component_;
public:
	ParamId(int objectID = 0, int component = 0)
        : objectID_(objectID), component_(component) {}

	bool operator==(const ParamId& other)const {
        return objectID_ == other.objectID_ && component_ == other.component_;
	}

    bool operator!=(const ParamId& other) const {
        return !(*this == other);
    }

    bool operator<(const ParamId& other) const {
        if (objectID_ != other.objectID_) {
            return objectID_ < other.objectID_;
        }
        return component_ < other.component_;
    }

    int getObjectID() const { return objectID_; }
    int getComponent() const { return component_; }
};
