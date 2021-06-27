import java.util.ArrayList;

public class Buckets {
	ArrayList<Trace>  traces = new ArrayList<Trace>();
	public void add(Trace trace) {
		traces.add(trace);
	}
	public String toString() {
		StringBuilder str = new StringBuilder("");
        for(int i=0; i< traces.size(); i++){
            str.append(traces.get(i).m + " " + traces.get(i).n + "\n");
        }
		return str.toString();
	}
}
