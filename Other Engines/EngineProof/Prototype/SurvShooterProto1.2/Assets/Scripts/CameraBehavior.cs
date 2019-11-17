using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraBehavior : MonoBehaviour
{
    Player p;
    ShakeBehavior shake;
    public float shakeTimerMax;
    float shaketimer;
    Vector3 ogPos;

    // Start is called before the first frame update
    void Start()
    {
        p = GameObject.Find("Player").GetComponent<Player>();
        shake = GetComponent<ShakeBehavior>();
        ogPos = transform.position;
    }

    // Update is called once per frame
    void Update()
    {
        if (p.PlayerShake)
        {
            shaketimer += Time.deltaTime;
            shake.Shaking(gameObject);
        }

        if (shaketimer > shakeTimerMax)
        {
            p.PlayerShake = false;
            shaketimer = 0f;
            transform.position = ogPos;
        }
    }
}
