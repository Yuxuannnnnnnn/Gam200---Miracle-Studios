using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerCollisionBehavior : MonoBehaviour
{
    Player p;

    void Start()
    {
        p = GetComponentInParent<Player>();
    }

    void OnCollisionEnter2D(Collision2D coll)
    {
        switch (coll.gameObject.tag)
        {
            case "Enemy Bullet":
                p.PlayerShake = true;
                p.Health--;
                break;
            default:
                break;
        }
    }
}
