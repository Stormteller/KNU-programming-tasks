package com.univ.labs;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;
import org.xml.sax.SAXException;


public class CandiesSAXParser {
    public static void main(String[] args) {
        try {
            SAXParserFactory saxPF = SAXParserFactory.newInstance();
            SAXParser saxP = saxPF.newSAXParser();
            CandiesSAXHandler Handler = new CandiesSAXHandler();
            File file = new File("Candies.xml");
            saxP.parse(file, Handler);
            ArrayList<Candy> candies = Handler.getCandies();
            System.out.println(candies);
            Collections.sort(candies, new SortByEnergy());
            System.out.println("------------------\nSorted candies: "
                    + candies);

        } catch (ParserConfigurationException | SAXException | IOException ex) {
            ex.printStackTrace();
        }
    }
}