using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Player : MonoBehaviour
{
    float currHealth;
    public float maxHealth;
    public Transform HealthBar;
    Vector3 healthscale;

    int xp;
    int level;
    int xptolevel = 10;
    float bulletspeedmod;

    float oldMaxHealth;

    bool isLevel;
    bool isShaking = false;

    string currGun;

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

    public int XP
    {
        get
        {
            return xp;
        }
        set
        {
            xp = value;
        }
    }

    public bool Levelled
    {
        get
        {
            return isLevel;
        }
        set
        {
            isLevel = value;
        }
    }

    public int XPToLevel
    {
        get
        {
            return xptolevel;
        }
        set
        {
            xptolevel = value;
        }
    }

    public float BulletSpeed
    {
        get
        {
            return bulletspeedmod;
        }
        set
        {
            bulletspeedmod = value;
        }
    }

    public string Gun
    {
        get { return currGun; }
        set { currGun = value; }
    }

    public bool PlayerShake
    {
        get { return isShaking; }
        set { isShaking = value; }
    }

    // Start is called before the first frame update
    void Start()
    {
        Health = oldMaxHealth = maxHealth;
        healthscale = HealthBar.transform.localScale;        
        healthscale.x = maxHealth / 10;
        HealthBar.transform.localScale = healthscale;

        XP = 0;
        level = 1;
        Gun = "Basic PewPew";
    }

    // Update is called once per frame
    void Update()
    {
        healthscale.x = currHealth / maxHealth;
        HealthBar.transform.localScale = healthscale;

        if (currHealth <= 0)
        {
            Destroy(gameObject);
        }
        else if (currHealth > maxHealth)
        {
            currHealth = maxHealth;
        }

        if (maxHealth > oldMaxHealth)
        {
            //healthscale.x = maxHealth / maxHealth;
            currHealth = maxHealth;
            oldMaxHealth = maxHealth;
        }

        if (xp >= xptolevel)
        {
            level++;
            Levelled = true;
            xp -= XPToLevel;
            xptolevel *= 2;
        }
    }
}