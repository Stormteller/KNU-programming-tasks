package com.univ.labs;

import javax.xml.stream.XMLInputFactory;
import javax.xml.stream.XMLStreamException;
import javax.xml.stream.XMLStreamReader;
import javax.xml.transform.stream.StreamSource;

public class CandiesStAXParser {
    public static void main(String[] args) throws XMLStreamException {
        try {
            XMLInputFactory f = XMLInputFactory.newInstance();
            XMLStreamReader reader = f.createXMLStreamReader(new StreamSource("Candies.xml"));
            CandiesStAXParserHandler handler = new CandiesStAXParserHandler(reader);
            System.out.println(handler.getCandies());

        } catch (XMLStreamException ex) {
            ex.printStackTrace();
        }

    }
}
