using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerMovementBehavior : MonoBehaviour
{
    public float maxSpeed;
    float xAxis;
    float yAxis;

    Player p;
    UIMenu ui;

    // Start is called before the first frame update
    void Start()
    {
        p = GameObject.Find("Player").GetComponent<Player>();
        ui = GameObject.Find("GameController").GetComponent<UIMenu>();
    }

    // Update is called once per frame
    void Update()
    {
        Vector3 moveVec = new Vector3(0,0,0);

        if (!p.Levelled || !ui.Paused)
        {
            xAxis = Input.GetAxis("Horizontal") * 0.5f;
            yAxis = Input.GetAxis("Vertical") * 0.5f;
        }

        if (p.Levelled || ui.Paused)
        {
            xAxis = yAxis = 0f;
        }

        moveVec.x = xAxis;
        moveVec.y = yAxis;

        transform.Translate(moveVec * maxSpeed);
    }
}
