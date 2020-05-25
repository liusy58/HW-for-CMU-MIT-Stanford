package bearmaps.proj2c;

import bearmaps.hw4.streetmap.Node;
import bearmaps.hw4.streetmap.StreetMapGraph;
import bearmaps.proj2ab.Point;
import bearmaps.proj2ab.WeirdPointSet;
import org.eclipse.jetty.util.Trie;

import java.util.*;
import java.util.function.Predicate;

/**
 * An augmented graph that is more powerful that a standard StreetMapGraph.
 * Specifically, it supports the following additional operations:
 *
 *
 * @author Alan Yao, Josh Hug, Siyu Liu
 */
public class AugmentedStreetMapGraph extends StreetMapGraph {
    private WeirdPointSet points;
    private HashMap<Point,Node> point2node;
    private HashMap<String,ArrayList<Point>>name2pos;
    private PrifixTree prefix_tree;
    public AugmentedStreetMapGraph(String dbPath) {
        super(dbPath);
        // You might find it helpful to uncomment the line below:
        List<Node> nodes = this.getNodes();
        point2node=new HashMap<Point,Node>();
        ArrayList<Point>_points=new ArrayList<>();
        prefix_tree=new PrifixTree();
        name2pos=new HashMap<>();
        System.out.println("The nodes are below:");
        for(int i=0;i<nodes.size();++i)
        {

            Node node=nodes.get(i);
            if(node.name()!=null)
                prefix_tree.insert(node.name());

//            if(super.neighbors(node.id()).isEmpty())
//                continue;
            Point point=new Point(node.lon(),node.lat());
            point2node.put(point,node);
            if(node.name()!=null)
            {
                String name=new String(node.name());

                name=cleanString(name);
                //System.out.println("The node name is "+node.name()+"the simple is :"+name);
                if(name2pos.get(name)!=null)
                {
                    name2pos.get(name).add(point);
                }
                else
                {
                    ArrayList<Point>temp=new ArrayList<>();
                    temp.add(point);
                    name2pos.put(name,temp);
                }
            }
            if(super.neighbors(node.id()).isEmpty())
                continue;
            _points.add(point);

        }
        points = new WeirdPointSet(_points);
    }


    /**
     * For Project Part II
     * Returns the vertex closest to the given longitude and latitude.
     * @param lon The target longitude.
     * @param lat The target latitude.
     * @return The id of the node in the graph closest to the target.
     */
    public long closest(double lon, double lat) {
        Point res=points.nearest(lon,lat);
        return point2node.get(res).id();
    }


    /**
     * For Project Part III (gold points)
     * In linear time, collect all the names of OSM locations that prefix-match the query string.
     * @param prefix Prefix string to be searched for. Could be any case, with our without
     *               punctuation.
     * @return A <code>List</code> of the full names of locations whose cleaned name matches the
     * cleaned <code>prefix</code>.
     */
    public List<String> getLocationsByPrefix(String prefix) {

        ArrayList<String>res=new ArrayList<String>();
        prefix_tree.hasPrefix(prefix,res);
        return res;
    }

    /**
     * For Project Part III (gold points)
     * Collect all locations that match a cleaned <code>locationName</code>, and return
     * information about each node that matches.
     * @param locationName A full name of a location searched for.
     * @return A list of locations whose cleaned name matches the
     * cleaned <code>locationName</code>, and each location is a map of parameters for the Json
     * response as specified: <br>
     * "lat" -> Number, The latitude of the node. <br>
     * "lon" -> Number, The longitude of the node. <br>
     * "name" -> String, The actual name of the node. <br>
     * "id" -> Number, The id of the node. <br>
     */
    public List<Map<String, Object>> getLocations(String locationName) {
//        Iterator iter = name2pos.entrySet().iterator();
//        while (iter.hasNext()) {
//            Map.Entry entry = (Map.Entry) iter.next();
//            System.out.println("Key:"+entry.getKey()+"  Value:"+entry.getValue());
//        }
        System.out.println("the locationName is "+locationName);
        String name =cleanString(locationName);
        List<Map<String, Object>>res=new LinkedList<>();
        ArrayList<Point>points=name2pos.get(name);
        if(points==null)
        {
            System.out.println("the locationName is not mapped to any node!");
            return res;
        }

        for(Point point:points)
        {
            HashMap<String, Object>temp=new HashMap<>();
            temp.put("lat",point2node.get(point).lat());
            temp.put("lon",point2node.get(point).lon());
            temp.put("name",locationName);
            temp.put("id",point2node.get(point).id());
            res.add(temp);

            System.out.println("in getLocations: "+locationName);
        }
        return res;
    }


    /**
     * Useful for Part III. Do not modify.
     * Helper to process strings into their "cleaned" form, ignoring punctuation and capitalization.
     * @param s Input string.
     * @return Cleaned string.
     */
    private static String cleanString(String s) {
        return s.replaceAll("[^a-zA-Z]", "").toLowerCase();
    }

}
