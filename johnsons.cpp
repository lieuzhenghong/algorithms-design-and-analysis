/*
The following subroutine takes in  the following: 
    - Key value pair of schema:
    {
        int vertex : std:vector < std::array<double, 3> edge > edges
    }
    - An array of n length specifying the cost from the souce vertex V (set at 1)
    and every other vertex
and returns a:
    - Key value pair of that exact same schema.

How this subroutine works:

 Run through every vertex's edges. For each edge that points to it, it

Consider a path s-v. Each vertex has weight w_v.
For each edge from e that starts from a t and ends at u, add to the edge w_t - w_u.
This way, path length is invariant: the final path length is reweighted by w_s - w_v

We have a "fake" source vertex 

*/