using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class WallCollisionBehavior : MonoBehaviour
{
    Wall w;

    // Start is called before the first frame update
    void Start()
    {
        w = GetComponent<Wall>();
    }

    void OnCollisionEnter2D (Collision2D coll)
    {
        switch (coll.gameObject.tag)
        {
            case "Enemy":
            case "Enemy Bullet":
                w.Health--;
                break;
            default:
                break;
        }
    }
}
