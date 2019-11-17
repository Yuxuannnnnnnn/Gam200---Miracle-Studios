using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ShakeBehavior : MonoBehaviour
{
    public float shakeTime;
    public float shakeStrength;

    bool isShaking;

    IEnumerator shake;

    public bool Shake
    {
        get
        {
            return isShaking;
        }
        set
        {
            isShaking = value;
        }
    }

    void Update()
    {
        if (Shake)
        {
            Vector3 newPos = transform.position + (Random.insideUnitSphere * (Time.deltaTime * shakeStrength));
            newPos.y = transform.position.y;
            newPos.z = transform.position.z;

            transform.position = newPos;
        }
    }

    public void Shaking(GameObject g)
    {
        shake = ShakingNow(g);
        StartCoroutine(shake);
    }

    IEnumerator ShakingNow(GameObject gc)
    {
        Vector3 ogPos = gc.transform.position;
        if (!Shake)
        {            
            Shake = true;
        }

        yield return new WaitForSeconds(shakeTime);

        Shake = false;
        gc.transform.position = ogPos;
    }
}
