using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RotationBehavior : MonoBehaviour
{

    Vector3 rotf;
    float angle;
    TurretBehavior turret;

    // Start is called before the first frame update
    void Start()
    {
        if (gameObject.tag == "Turret")
        {
            turret = GetComponentInParent<TurretBehavior>();
        }
    }

    // Update is called once per frame
    void Update()
    {
        if (gameObject.tag == "Player")
        {
            rotf =
                Camera.main.ScreenToWorldPoint(Input.mousePosition);
        }
        if (gameObject.tag == "Turret")
        {
            if (turret.Target && turret.Target.tag == "Enemy")
            {
                rotf = turret.Target.transform.position;
            }                           
        }

        angle = Mathf.Atan2(rotf.y - transform.position.y,
            rotf.x - transform.position.x);

        float AngleDeg = angle * Mathf.Rad2Deg - 90f;

        transform.rotation = Quaternion.AngleAxis(AngleDeg, Vector3.forward);
    }
}
