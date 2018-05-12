#pragma once
#include <stdexcept>
#include <memory>
#include "Interface.hpp"


/* A simple Factory class for building all kind of interface*/
class InterfaceFactory
{
public:
    static std::shared_ptr<Interface> createInterface(InterfaceType type)
    {
    	/* This switch is very ugly, this interface can be moved to Inferface class as virtual function
    	 * and create a bunch of sub class.*/
        switch(type)
        {
        case InterfaceType::UU_GNB:
            return createUU_GNB_Interface();
        default:
            throw std::invalid_argument("The interface not support yet!");
        }
    }
protected:
    static std::shared_ptr<Interface> createUU_GNB_Interface()
    {
        Interface *result = new Interface();
        result->addProtocolAtBottom(new PDCP());
        result->addProtocolAtBottom(new RLC());
        result->addProtocolAtBottom(new MAC());
        result->addProtocolAtBottom(new PHY());
        return std::make_shared<Interface>(*result);
    }
};
