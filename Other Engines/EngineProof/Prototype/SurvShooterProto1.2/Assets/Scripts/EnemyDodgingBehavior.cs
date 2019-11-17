using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyDodgingBehavior : MonoBehaviour
{
    float cooldown;
    public float maxCooldown;

    // Start is called before the first frame update
    void Start()
    {
        cooldown = 0;
    }

    // Update is called once per frame
    void Update()
    {
        cooldown += Time.deltaTime;
    }

    void OnTriggerEnter2D(Collider2D coll)
    {

        if (coll.tag == "Bullet" && cooldown > maxCooldown)
        {
            transform.position += Vector3.up;
            cooldown = 0;
        }
    }
    void OnTriggerStay2D(Collider2D coll)
    {

    }

    void OnTriggerExit2D(Collider2D coll)
    {
    }
}
