using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class PlayerShootBehavior : PlayerSpawnItemBehavior
{
    float cooldown;
    public float maxCooldown;
    public Text ammoCount;
    public Text currGun;
    public int clipSize;
    int ammo;
    float reloadtimer;
    SoundController sound;
    Player p;

    int defaultammo;
    float defaultcooldown;

    int SFXpos;
    bool isRocket;

    // Start is called before the first frame update
    void Start()
    {
        ammo = defaultammo = clipSize;
        defaultcooldown = maxCooldown;
        sound = GameObject.Find("SoundController").GetComponent<SoundController>();
        p = GetComponent<Player>();
    }

    // Update is called once per frame
    void Update()
    {
        if (!isRocket)
        {
            StartCoroutine("RocketCheck");
        }

        Vector3 ammopos = Camera.main.ScreenToWorldPoint(Input.mousePosition);
        ammopos.z = 0f;
        ammopos.x += 0.6f;
        ammopos.y -= 0.6f;

        ammoCount.transform.position = ammopos;
        ammoCount.text = ammo.ToString();

        currGun.text = p.Gun;

        cooldown += Time.deltaTime;

        if ( (Input.GetMouseButtonDown(0) || Input.GetMouseButton(0)) 
            && (cooldown >= maxCooldown) && ammo > 0 && Time.timeScale > 0f)
        {
            ammo--;
            switch (p.Gun)
            {
                case "Rocket Launcher":
                    SFXpos = 1;
                    Instantiate(Spawnables[1],spawn.transform.position, spawn.transform.rotation);
                    break;
                default:
                    SFXpos = 0;
                    Instantiate(Spawnables[0], spawn.transform.position, spawn.transform.rotation);
                    break;
            }
            sound.PlaySound(sound.SFXList[SFXpos]);
            cooldown = 0.0f;
        }        

        if (ammo == 0)
        {
            reloadtimer += Time.deltaTime;
            ammoCount.text = "Reloading...";
            if (reloadtimer > 1.0f)
            {
                ammo = clipSize;
                reloadtimer = 0;
            }
            else if (ammo == 0 && p.Gun == "Rocket Launcher")
            {
                isRocket = false;
                ammo = clipSize = defaultammo;
                maxCooldown = defaultcooldown;
                p.Gun = "Default PewPew";
            }
        }
    }

    IEnumerator RocketCheck()
    {
        if (p.Gun == "Rocket Launcher")
        {
            ammo = clipSize;
            isRocket = true;
        }

        yield return new WaitForSeconds(1.0f);
    }
}