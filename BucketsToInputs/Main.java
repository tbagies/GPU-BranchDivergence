
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Random;
import java.util.Scanner;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.util.ArrayList;

public class Main{
 
    public static void main(String [] args)  throws FileNotFoundException{
        System.out.println("Enter Traces file name: ");
        Scanner scanner = new Scanner(System.in);
        String traceFile = scanner.nextLine();
        File file = new File(traceFile);
        Scanner scnr = new Scanner(file);
        ArrayList<String> traces = new ArrayList<String>();
        int k = 0, in=0;
        Trace aTrace;
        while(scnr.hasNextLine()){
            aTrace = new Trace();
            String line = scnr.nextLine();
            traces.add(line);
            //System.out.print("m n " +  split[2] + " " + split[3] + ", ");
        }
        
        scnr.close();
        
        int number_of_buckets = traces.size()/32;
        System.out.println("number_of_buckets " + number_of_buckets);
        ArrayList<String> bucket = new ArrayList<String>();//Buckets[number_of_buckets];
        System.out.println("Enter Buckets file name: ");
        scanner = new Scanner(System.in);
        String inFile = scanner.nextLine();
        file = new File(inFile);
        scnr = new Scanner(file);
        k =0;
        while(scnr.hasNextLine()){
	    		//bucket[k] = new Buckets();
	    		String line = scnr.nextLine();
	    		String[] ids = line.split(", ");
	    		for(int i =0; i< ids.length; i++) {
				//System.out.println(ids[i]);
				ids[i]=ids[i].replace("[","");
                                ids[i]=ids[i].replace("]","");
	    			int id = Integer.parseInt(ids[i]);
	    			bucket.add(traces.get(id));
	    		}
	        k++;
        }
        scnr.close();
        try{
            String f1 = "ArrangedInput.txt";
            System.out.println(f1);
            BufferedWriter writer = new BufferedWriter(new FileWriter(f1));
            for(int j=0; j<bucket.size(); j++) {
            		String output = bucket.get(j);//.toString();
            		writer.write(output + "\n");
            }
            writer.close();
        }catch(IOException e){
            System.out.println("IOException");
        }
    }
}
