using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Enemy : MonoBehaviour
{
    int health;
    public int maxHealth;
    GameControllerBehavior gc;
    public int EnemyHealth
    {
        get { return health; }
        set { health = value; }
    }

    // Start is called before the first frame update
    void Start()
    {
        gc = GameObject.Find("GameController")
        .GetComponent<GameControllerBehavior>();
        health = maxHealth;                    
        gc.EnemyCount++;
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
