package com.univ.labs;

public class Candy {
    private String ID;
    private String name;
    private int energy;
    private Type type;
    private Ingredients ingredients;
    private Value value;
    private String production;

    public String getID() {
        return ID;
    }

    public void setID(String ID) {
        this.ID = ID;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getEnergy() {
        return energy;
    }

    public void setEnergy(int energy) {
        this.energy = energy;
    }

    public Type getType() {
        return type;
    }

    public void setType(Type type) {
        this.type = type;
    }

    public Ingredients getIngredients() {
        return ingredients;
    }

    public void setIngredients(Ingredients ingredients) {
        this.ingredients = ingredients;
    }

    public Value getValue() {
        return value;
    }

    public void setValue(Value value) {
        this.value = value;
    }

    public String getProduction() {
        return production;
    }

    public void setProduction(String production) {
        this.production = production;
    }

    @Override
    public String toString() {
        return "\nName: " + this.name
                + "\nEnergy: " + this.energy + "\nProduction: " + this.production
                + "\nValue: \nProteins " + this.value.getProtein()
                + "\nFats: " + this.value.getFats()
                + "\nCarbohydrates: " + this.value.getCarbohydrates() + "\n\n";
    }
}
