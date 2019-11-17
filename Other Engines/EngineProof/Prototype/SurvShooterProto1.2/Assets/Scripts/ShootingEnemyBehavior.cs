using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ShootingEnemyBehavior : BasicEnemyBehavior
{
    float cooldown;
    public float maxCooldown;
    bool isStopped = false;

    Vector3 pLoc;

    // Update is called once per frame
    protected override void Update()
    {
        if (player)
        {
            pLoc = player.transform.position;
        }

        if (!ui.Paused)
        {
            Rotate(pLoc);

            if (cooldown > maxCooldown && cooldown > 0)
            {
                transform.Translate(Vector3.zero);
                isStopped = true;
            }
            else if (!isStopped)
            {
                cooldown += Time.deltaTime;
                base.Update();
            }

            if (isStopped)
            {
                cooldown -= Time.deltaTime;
                if (cooldown < 0)
                {
                    isStopped = false;
                }
            }
        }
        else
        {
            transform.Translate(Vector3.zero);
        }
    }
}
