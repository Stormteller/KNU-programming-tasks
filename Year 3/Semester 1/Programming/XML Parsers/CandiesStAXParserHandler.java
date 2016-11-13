package com.univ.labs;

import javax.xml.stream.XMLStreamConstants;
import javax.xml.stream.XMLStreamException;
import javax.xml.stream.XMLStreamReader;
import java.util.ArrayList;

public class CandiesStAXParserHandler {
    private XMLStreamReader reader;
    private ArrayList<Candy> candies;
    Type currentType;
    Ingredients currentIngredients;
    Value currentValue;
    Candy currentCandy;
    Row state;
    boolean flag;


    public ArrayList<Candy> getCandies() {
        return this.candies;
    }

    public CandiesStAXParserHandler(XMLStreamReader reader) throws XMLStreamException {
        candies = new ArrayList<>();
        this.reader = reader;
        handle();
    }

    public void handle() throws XMLStreamException {
        flag = false;
        while (reader.hasNext()) {
            String qName = null;
            int i = reader.next();
            switch (i) {
                case XMLStreamConstants.START_ELEMENT:
                    qName = reader.getLocalName();
                    if (reader.getLocalName() == "candy") {
                        currentCandy = new Candy();
                        currentValue = new Value();
                        currentIngredients = new Ingredients();
                        currentType = new Type();
                        this.currentCandy.setID(reader.getAttributeValue(0));
                    }
                    if (qName.equals("Name") || qName.equals("Energy")
                            || qName.equals("Caramel") || qName.equals("Filling")
                            || qName.equals("Chocolate") || qName.equals("Water")
                            || qName.equals("Sugar") || qName.equals("Fructose")
                            || qName.equals("Vanillin") || qName.equals("Protein")
                            || qName.equals("Fats") || qName.equals("Carbohydrates")
                            || qName.equals("Production")) {
                        flag = true;
                        state = Row.valueOf(qName.toUpperCase());
                    }
                    break;
                case XMLStreamConstants.END_ELEMENT:
                    qName = reader.getLocalName();
                    if (qName.equals("candy")) {
                        candies.add(currentCandy);
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
                    state = null;
                    flag = false;
                    break;
                case XMLStreamConstants.CHARACTERS:
                    String str = reader.getText();
                    if (flag) {
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
                    break;
            }
        }
    }
}
