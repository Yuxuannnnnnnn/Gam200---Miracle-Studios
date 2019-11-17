using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RocketPowUpBehavior : PowerUpBehavior
{
    PlayerShootBehavior pshoot;
    public int clipSize;
    public float maxCooldown;

    protected override void Start()
    {
        base.Start();
        pshoot = p.GetComponent<PlayerShootBehavior>();
    }

    // Start is called before the first frame update
    protected override void OnTriggerEnter2D(Collider2D coll)
    {
        if (coll.tag == "Player")
        {
            p.Gun = "Rocket Launcher";
            pshoot.clipSize = 5;
            pshoot.maxCooldown = 2f;
            Destroy(gameObject);
        }
    }
}
