using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DrawLineBehavior : MonoBehaviour
{
    LineRenderer lr;
    float dist;
    float counter;

    public Vector3 p0, p1;
    public float drawSpeed = 0f;

    Player p;

    // Start is called before the first frame update
    void Start()
    {

        p = GameObject.FindGameObjectWithTag("Player").GetComponent<Player>();
        lr = GetComponent<LineRenderer>();

        p0 = transform.position;
        p1 = p.transform.position;

        lr.positionCount = 2;
        lr.SetPosition(0, p0);
        dist = Vector3.Distance(p0, p1);
    }

    // Update is called once per frame
    void Update()
    {
        if (counter < dist)
        {
            counter += 0.1f / drawSpeed;

            float x = Mathf.Lerp(0, dist, counter);
            var point0 = p0;
            var point1 = p1;

            var pointALongLine = x * Vector3.Normalize(p1 - p0) + p0;

            lr.SetPosition(1, pointALongLine);
        }
    }
}
