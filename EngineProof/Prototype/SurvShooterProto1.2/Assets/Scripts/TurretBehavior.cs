using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TurretBehavior : MonoBehaviour    
{
    GameObject targetEnemy;
    float cooldown;
    public float maxCooldown;
    public Transform spawn;
    public GameObject bullet;

    public GameObject Target
    {
        get
        {
            return targetEnemy;
        }
    }

    // Update is called once per frame
    void Update()
    {
        if (Target)
        {
            cooldown += Time.deltaTime;
            if (cooldown >= maxCooldown)
            {
                Shoot();
                cooldown = 0f;
            }
        }
    }

    void OnTriggerEnter2D(Collider2D coll)
    {
        if (coll.gameObject.tag == "Enemy")
        {
            targetEnemy = coll.gameObject;
        }
    }

    void OnTriggerStay2D(Collider2D coll)
    {
        if (targetEnemy == null && coll.gameObject.tag == "Enemy")
        {
            targetEnemy = coll.gameObject;
        }
    }

    void OnTriggerExit2D(Collider2D coll)
    {
        if (coll.gameObject.tag == "Enemy")
        {
            targetEnemy = null;
        }
    }

    void Shoot()
    {
        Instantiate(bullet, spawn.position, spawn.rotation);
    }
}
