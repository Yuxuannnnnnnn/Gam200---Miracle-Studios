using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BulletMovementBehavior : MonoBehaviour
{
    SpriteRenderer sr;
    public float maxSpeed;
    string parentTag;
    Player p;
    UIMenu ui;

    // Start is called before the first frame update
    void Start()
    {
        sr = GetComponent<SpriteRenderer>();
        parentTag = gameObject.tag;
        p = GameObject.Find("Player")
            .GetComponent<Player>();
        ui = GameObject.Find("GameController")
            .GetComponent<UIMenu>();
    }

    // Update is called once per frame
    void Update()
    {
        if (!ui.Paused && !p.Levelled)
        {
            if (parentTag == "Bullet")
            {
                transform.Translate(Vector3.up * (maxSpeed + p.BulletSpeed));
            }
            else
            {
                transform.Translate(Vector3.up * maxSpeed);
            }
        }
        else
        {
            transform.Translate(Vector3.zero);
        }

        if (!sr.isVisible)
        {
            Destroy(gameObject);
        }
    }
}
