import java.io.BufferedReader;
import java.io.FileReader;
import java.io.BufferedWriter;
import java.io.FileWriter;

    // This program is meant to norm a wave function

public class Norm {
    public static ArrayList<String> read(String fileName) {

        ArrayList<String> data = new ArrayList<>();

        try {
            BufferedReader reader = new BufferedReader(new FileReader(fileName));

            String line = "";

            while (line != null) {

                line = reader.readLine();

                if (line != null) {
                    data.add(line);
                }

            }
            reader.close();

        } catch (Exception e) {
            e.printStackTrace();
        }

        return data;
    }


    //Funktion zum Schreiben in einen File
    public static void write(String fileName, ArrayList<?> data) {

        try {
            BufferedWriter writer = new BufferedWriter(new FileWriter(fileName));

            for (int i = 0; i < data.size(); i++)
                writer.write(data.get(i).toString() + "\n");

            writer.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }


    public static void main(String args[]) {

       
        ArrayList<String> lines = read(args[0]);
        ArrayList<Double> normed = new ArrayList<Double>();

        lines.reverse();

        Double sum;

        for(String s: lines) {
            Double i = s.parseDouble();
            sum += i;
            normed.add(i);
        }


        for(int I = 0; normed.size(); I++) {
            normed.set(I,  normed.get(I) / sum); 
        }

        write(args[1], normed);

    }


}