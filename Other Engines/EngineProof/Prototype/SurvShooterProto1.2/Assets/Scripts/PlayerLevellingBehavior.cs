using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerLevellingBehavior : MonoBehaviour
{
    public GameObject LevelUpMenu;
    public Transform LevelUpBar;
    Player p;
    Vector3 xpscale = Vector3.one;

    // Start is called before the first frame update
    void Start()
    {
        p = GetComponent<Player>();
        LevelUpMenu.SetActive(false);
        xpscale.x = p.XP;
        LevelUpBar.localScale = xpscale;
    }

    // Update is called once per frame
    void Update()
    {
        xpscale.x = ((float)p.XP / (float)p.XPToLevel);
        LevelUpBar.localScale = xpscale;

        if (p.Levelled)
        {
            Time.timeScale = 0f;
            LevelUpMenu.SetActive(true);         
        }
        else
        {
            Time.timeScale = 1f;
            LevelUpMenu.SetActive(false);            
        }
    }

    public void LevelUpHealth()
    {
        p.maxHealth += 5;
        p.Levelled = false;
    }

    public void LevelUpBulletSpeed()
    {
        p.BulletSpeed += 0.1f;
        p.Levelled = false;
    }
}