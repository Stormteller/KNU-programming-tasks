package com.univ.labs;


import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import java.util.ArrayList;

public class CandiesBuildDOM {
    public static ArrayList<Candy> candiesList(Element root) {
        ArrayList<Candy> candies = new ArrayList<>();
        Element elem = getChild(root, "candies");
        NodeList candiesNodes = elem.getElementsByTagName("candy");
        Candy candy;
        Type type;
        Ingredients ingredients;
        Value value;
        for (int i = 0; i < candiesNodes.getLength(); i++) {
            candy = new Candy();
            type = new Type();
            ingredients = new Ingredients();
            value = new Value();
            Element candyElem = (Element) candiesNodes.item(i);
            candy.setName(getChildValue(candyElem, "Name"));
            candy.setEnergy(Integer.parseInt(getChildValue(candyElem, "Energy")));

            type.setCaramel(Boolean.parseBoolean(getChildValue(getChild(candyElem, "Type"), "Caramel")));
            type.setFilling(Boolean.parseBoolean(getChildValue(getChild(candyElem, "Type"), "Filling")));
            type.setChocolate(Boolean.parseBoolean(getChildValue(getChild(candyElem, "Type"), "Chocolate")));
            candy.setType(type);

            ingredients.setWater(Integer.parseInt(getChildValue(getChild(candyElem, "Ingredients"), "Water")));
            ingredients.setSugar(Integer.parseInt(getChildValue(getChild(candyElem, "Ingredients"), "Sugar")));
            ingredients.setFructose(Integer.parseInt(getChildValue(getChild(candyElem, "Ingredients"), "Fructose")));
            ingredients.setVanillin(Integer.parseInt(getChildValue(getChild(candyElem, "Ingredients"), "Vanillin")));
            candy.setIngredients(ingredients);

            value.setProtein(Integer.parseInt(getChildValue(getChild(candyElem, "Value"), "Protein")));
            value.setFats(Integer.parseInt(getChildValue(getChild(candyElem, "Value"), "Fats")));
            value.setCarbohydrates(Integer.parseInt(getChildValue(getChild(candyElem, "Value"), "Carbohydrates")));
            candy.setValue(value);

            candy.setProduction(getChildValue(candyElem, "Production"));
            candies.add(candy);
        }
        return candies;
    }

    private static Element getChild(Element parent, String childName) {
        NodeList nlst = parent.getElementsByTagName(childName);
        Element child = (Element) nlst.item(0);
        return child;
    }

    private static String getChildValue(Element parent, String childName) {
        Element child = getChild(parent, childName);
        Node node = child.getFirstChild();
        return node.getNodeValue();
    }
}
