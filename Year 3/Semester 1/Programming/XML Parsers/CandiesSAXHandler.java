package com.univ.labs;


import java.util.ArrayList;
import org.xml.sax.Attributes;
import org.xml.sax.helpers.DefaultHandler;

enum Row { NAME, ENERGY, CARAMEL, FILLING, CHOCOLATE, WATER, SUGAR, FRUCTOSE, VANILLIN, PROTEIN, FATS, CARBOHYDRATES, PRODUCTION }

public class CandiesSAXHandler extends DefaultHandler {
    ArrayList<Candy> candies = new ArrayList<>();
    Type currentType;
    Ingredients currentIngredients;
    Value currentValue;
    Candy currentCandy;
    Row state;

    public ArrayList<Candy> getCandies() {
        return this.candies;
    }

    @Override
    public void startDocument() {
        System.out.println("Start document");
    }

    @Override
    public void startElement(String uri, String localName,
                             String qName, Attributes attributes) {
        if (qName.equals("candy")) {
            currentCandy = new Candy();
            currentValue = new Value();
            currentIngredients = new Ingredients();
            currentType = new Type();
            this.currentCandy.setID(attributes.getValue(0));
        }
        if (qName.equals("Name") || qName.equals("Energy")
                || qName.equals("Caramel") || qName.equals("Filling")
                || qName.equals("Chocolate") || qName.equals("Water")
                || qName.equals("Sugar") || qName.equals("Fructose")
                || qName.equals("Vanillin") || qName.equals("Protein")
                || qName.equals("Fats") || qName.equals("Carbohydrates")
                || qName.equals("Production")) {
            this.state = Row.valueOf(qName.toUpperCase());
        }
    }

    @Override
    public void endElement(String uri, String localName, String qName) {
        if (qName.equals("candy")) {
            this.candies.add(currentCandy);
        }
        if (qName.equals("Type")) {
            this.currentCandy.setType(currentType);
        }
        if (qName.equals("Ingredients")) {
            this.currentCandy.setIngredients(currentIngredients);
        }
        if (qName.equals("Value")) {
            this.currentCandy.setValue(currentValue);
        }
        this.state = null;
    }

    @Override
    public void characters(char[] ch, int start, int length) {
        String str = new String(ch, start, length).trim();
        if (str.length() > 0) {
            switch (this.state) {
                case NAME:
                    this.currentCandy.setName(str);
                    break;
                case ENERGY:
                    int energy = Integer.parseInt(str);
                    this.currentCandy.setEnergy(energy);
                    break;
                case CARAMEL:
                    boolean caramel = Boolean.parseBoolean(str);
                    this.currentType.setCaramel(caramel);
                    break;
                case FILLING:
                    boolean filling = Boolean.parseBoolean(str);
                    this.currentType.setFilling(filling);
                    break;
                case CHOCOLATE:
                    boolean chocolate = Boolean.parseBoolean(str);
                    this.currentType.setChocolate(chocolate);
                    break;
                case WATER:
                    int water = Integer.parseInt(str);
                    this.currentIngredients.setWater(water);
                    break;
                case SUGAR:
                    int sugar = Integer.parseInt(str);
                    this.currentIngredients.setSugar(sugar);
                    break;
                case FRUCTOSE:
                    int fructose = Integer.parseInt(str);
                    this.currentIngredients.setFructose(fructose);
                    break;
                case VANILLIN:
                    int vanillin = Integer.parseInt(str);
                    this.currentIngredients.setVanillin(vanillin);
                    break;
                case PROTEIN:
                    int protein = Integer.parseInt(str);
                    this.currentValue.setProtein(protein);
                    break;
                case FATS:
                    int fats = Integer.parseInt(str);
                    this.currentValue.setFats(fats);
                    break;
                case CARBOHYDRATES:
                    int carbohydrates = Integer.parseInt(str);
                    this.currentValue.setCarbohydrates(carbohydrates);
                    break;
                case PRODUCTION:
                    this.currentCandy.setProduction(str);
                    break;
            }
        }
    }
}