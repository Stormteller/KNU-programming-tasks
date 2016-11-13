package com.univ.labs;


import org.xml.sax.SAXException;

import javax.xml.transform.Source;
import javax.xml.transform.stream.StreamSource;
import javax.xml.validation.Schema;
import javax.xml.validation.SchemaFactory;
import javax.xml.validation.Validator;
import java.io.File;
import java.io.IOException;

public class CandiesValidator {

    public static void main(String[] args) throws SAXException, IOException {
        SchemaFactory factory = SchemaFactory.newInstance("http://www.w3.org/2001/XMLSchema");
        Schema schema = factory.newSchema(new File("Candies.xsd"));
        Validator validator = schema.newValidator();

        Source source = new StreamSource("Candies.xml");
        try {
            validator.validate(source);
            System.out.println("XML is valid");
        } catch (SAXException ex) {
            System.err.println("XML is invalid");
        }
    }
}
