package file_handling ;
import java.io.*;

public class File_handling
{
    public static String readFile(String fileName) throws IOException {       //It is a function to read from the file // throws : for tellinh that the method may give some I/O errors
        StringBuilder sb = new StringBuilder(); //Stringbuilder allows you to modify content without using new objects internally it is a variable size array
                                                // string methods create new instances wsting space and time , i.e once created , they are immutable
        try (BufferedReader br = new BufferedReader(new FileReader(fileName))) {    //Using file reader you can only take char by char so by combining BufferedReader u can read line by line
            String line;
            while ((line = br.readLine()) != null) {
                sb.append(line);
                sb.append("\n");
            }
        }
        return sb.toString();              //Converts StringBuider into string
    }

    public static void writeFile(String fileName, String data) throws IOException {
        try (BufferedWriter bw = new BufferedWriter(new FileWriter(fileName))) { //Using only FileWriter would also work fine but if the input data is large it is better to use bw bcz of performance
            bw.write(data);
        }
    }

    public static int countWords(String text) {
        String[] words = text.split("\\s+");   //Splits the text into array of strings
        return words.length;                    //Number of words
    }

    public static int countSentences(String text) {
        String[] sentences = text.split("[.!?]+");        //Array of sentences
        return sentences.length;
    }

    public static int find_occurences(String text,String word){
        String[] words = text.split(word);
        return words.length-1 ;
    }



    public static void main(String[] args) {
        // Test file reading, processing, and writing
        String inputFile = "src/file_handling/input.txt";
        String outputFile = "src/file_handling/output.txt";

        try {
            String text = readFile(inputFile);
            System.out.println("Original Text:");
            System.out.println(text);

            int wordCount = countWords(text);
            int sentenceCount = countSentences(text);

            System.out.println("Word count: " + wordCount);
            System.out.println("Sentence count: " + sentenceCount);
            System.out.println("java word count: " + find_occurences(readFile("src/file_handling/input.txt"),"Java"));

            // Replace a word
            //String newText = replaceWord(text, "Java", "Python");
            String newText = text.replaceAll("Java","Python");
            writeFile(outputFile, newText);
            System.out.println("Output file written successfully.");
        } catch (IOException e) {
            System.err.println("Error: " + e.getMessage());
        }
    }
}
