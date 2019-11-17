using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyShootBehavior : MonoBehaviour
{
    float cooldown;
    public float maxCooldown;
    public GameObject bullet;
    public Transform spawn;
    UIMenu ui;

    // Start is called before the first frame update
    void Start()
    {
        ui = GameObject.Find("GameController")
            .GetComponent<UIMenu>();
    }

    // Update is called once per frame
    void Update()
    {
        cooldown += Time.deltaTime;
        if (!ui.Paused && cooldown >= maxCooldown)
        {
            Instantiate(bullet, spawn.position, spawn.rotation);
            cooldown = 0;
        }
    }
}
