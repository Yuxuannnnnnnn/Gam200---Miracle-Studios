using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyCollisionBehavior : MonoBehaviour
{
    Player p;
    Enemy e;
    //ShakeBehavior shake;

    public int xpgiven;
    public List<GameObject> powup;
    public GameObject DeathEffect;

    GameControllerBehavior gc;
    SpriteRenderer sr;

    void Start()
    {
        p = GameObject.Find("Player")
            .GetComponent<Player>();
        e = GetComponent<Enemy>();
        gc = GameObject.Find("GameController")
             .GetComponent<GameControllerBehavior>();
        sr = GetComponent<SpriteRenderer>();
    }

    void Update()
    {
        if (e.EnemyHealth <= 0)
        {
            p.XP += xpgiven;
            GeneratePowerUp();
            gc.EnemyCount--;
            Instantiate(DeathEffect,transform.position, Quaternion.identity);
            Destroy(gameObject);
        }
    }

    void OnCollisionEnter2D(Collision2D coll)
    {
        if (sr.isVisible)
        {
            switch (coll.gameObject.tag)
            {
                case "Player":
                    p.Health--;
                    break;
                case "Wall":
                    break;
                case "Bullet":
                    e.EnemyHealth--;                    
                    break;
                default:
                    break;
            }
        }
    }

    void GeneratePowerUp()
    {
        int pow = Random.Range(0,10);
        int powtype = Random.Range(0, powup.Count);

        if (pow > 7)
        {
            Instantiate(powup[powtype], transform.position, Quaternion.identity);
        }
    }
}