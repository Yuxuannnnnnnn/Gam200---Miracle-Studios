using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Wall : MonoBehaviour
{
    float currHealth;
    public float maxHealth;
    SpriteRenderer sr;
    public GameObject WallHealth;

    public float Health
    {
        get
        {
            return currHealth;
        }
        set
        {
            currHealth = value;
        }
    }

    // Start is called before the first frame update
    void Start()
    {
        Health = maxHealth;
        sr = GetComponent<SpriteRenderer>();
    }

    // Update is called once per frame
    void Update()
    {
        Vector3 healthscale;
        healthscale = WallHealth.transform.localScale;
        healthscale.x = currHealth / 10;
        WallHealth.transform.localScale = healthscale;

        if (currHealth <= 0)
        {
            Destroy(gameObject);
        }
        else if (currHealth <= 5)
        {
            Color currColor;
            currColor = sr.color;
            currColor.a = 0.5f;
            sr.color = currColor;
        }
    }
}