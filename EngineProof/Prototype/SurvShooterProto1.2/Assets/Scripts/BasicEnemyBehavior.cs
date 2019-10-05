using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BasicEnemyBehavior : MonoBehaviour
{
    protected GameObject player;
    public float maxSpeed;
    protected UIMenu ui;
    protected Player p;

    // Start is called before the first frame update
    protected virtual void Start()
    {
        player = GameObject.Find("Player");
        p = player.GetComponent<Player>();
        ui = GameObject.Find("GameController")
            .GetComponent<UIMenu>();
    }

    // Update is called once per frame
    protected virtual void Update()
    {
        Vector3 pLoc = player.transform.position;

        if(!ui.Paused && !p.Levelled)
        {
            if (player)
            {
                Rotate(pLoc);
                transform.Translate(Vector3.up * maxSpeed);
            }            
        }
        else
        {
            transform.Translate(Vector3.zero);
        }
    }

    protected void Rotate(Vector3 location)
    {        
        Vector3 toPlayer = transform.position - location;
        float angle = Mathf.Atan2(toPlayer.y, toPlayer.x);
        float AngleDeg = angle * Mathf.Rad2Deg + 90f;
        transform.rotation = Quaternion.AngleAxis(AngleDeg, Vector3.forward);        
    }
}
