using System;
using System.Net;
using System.Net.Sockets;
using System.Text;

class UDPClient
{
    static void Main(string[] args)
    {
        string serverIP = "127.0.0.1";
        int serverPort = 20042;

        UdpClient clientSocket = new UdpClient();

        try
        {
            while (true)
            {
                Console.Write("Enter the computer component (type 'exit' to quit): ");
                string component = Console.ReadLine();

                if (component.ToLower() == "exit")
                    break;

                byte[] requestData = Encoding.ASCII.GetBytes(component);
                IPEndPoint serverEndPoint = new IPEndPoint(IPAddress.Parse(serverIP), serverPort);
                clientSocket.Send(requestData, requestData.Length, serverEndPoint);

                byte[] responseData = clientSocket.Receive(ref serverEndPoint);
                string response = Encoding.ASCII.GetString(responseData);

                Console.WriteLine($"Price for {component}: {response}");
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine($"An error: {ex.Message}");
        }
        finally
        {
            clientSocket.Close();
        }
    }
}
