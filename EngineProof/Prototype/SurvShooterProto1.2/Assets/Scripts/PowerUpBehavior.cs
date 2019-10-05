using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PowerUpBehavior : MonoBehaviour
{
    protected Player p;
    float vis;

    // Start is called before the first frame update
    protected virtual void Start()
    {
        vis = 0f;
        p = GameObject.Find("Player").GetComponent<Player>();
    }

    protected virtual void Update()
    {
        vis += Time.deltaTime;
        if (vis >= 6.0f)
        {
            Destroy(gameObject);
        }
    }

    protected virtual void OnTriggerEnter2D(Collider2D coll)
    {
        if (coll.tag == "Player")
        {
            p.Health += 2;
            Destroy(gameObject);
        }
    }
}
