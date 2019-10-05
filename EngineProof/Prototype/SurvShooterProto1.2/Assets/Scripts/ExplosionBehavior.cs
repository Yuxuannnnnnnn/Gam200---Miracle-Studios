using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ExplosionBehavior : MonoBehaviour
{

    public float maxDecay;
    float decay;
    int enemycount;

    public int explosiondamage;
    // Start is called before the first frame update
    void Start()
    {        
        decay = 0;
    }

    // Update is called once per frame
    void Update()
    {
        decay += Time.deltaTime;
        if (decay > maxDecay)
        {
            Destroy(gameObject);
        }
    }

    void OnTriggerEnter2D(Collider2D coll)
    {
        if (coll.tag == "Enemy")
        {
            coll.GetComponent<Enemy>().EnemyHealth--;
        }
    }
    void OnTriggerStay2D(Collider2D coll)
    {
        if (coll.tag == "Enemy")
        {
            coll.GetComponent<Enemy>().EnemyHealth--;
        }
    }

    void OnTriggerExit2D(Collider2D coll)
    {
    }
}
